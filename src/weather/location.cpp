/***************************************************************************
 *  Weather Desktop - An advanced, cross-platform weather application.     *
 *  Copyright (C) 2013  Michael Spencer <spencers1993@gmail.com>           *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/


#include "weather/location.h"
#include "wunderground/wunderground.h"

#include <QDateTime>
#include <QTimer>

bool Weather::Location::s_autoRefresh = false;
int Weather::Location::s_refreshTime = 60 * 60 * 1000; // 1 hour
Cache *Weather::Location::s_cache = nullptr;
Weather::Service *Weather::Location::s_defaultService = nullptr;
Weather::Units Weather::Location::s_units(Weather::Units::English);

Weather::Location::Location(const QString& name, const QString& location, Weather::Service *service, QObject* parent)
	: QObject(parent)
{
	Q_ASSERT(!location.isEmpty());
	
	// Use the default location if none is given
	if (service == nullptr) {
		Q_ASSERT(defaultService() != nullptr);
		
		service = defaultService();
	}
	
	// TODO: Normalize the location
	// Set the name and location
	setName(name);
	setLocation(location);
	setCoder(new Geocoding(location, this));
	QObject::connect(this, SIGNAL(locationChanged(QString)), coder(), SLOT(setLocation(QString)));
	QObject::connect(this, SIGNAL(locationChanged(QString)), coder(), SLOT(run()));
	QObject::connect(coder(), SIGNAL(coordinatesChanged(QString)), this, SLOT(setCoordinates(QString)));
	coder()->run();
	
	// Set the service
	setService(service);
	// Create the necessary weather types
	setConditions(this->service()->create_conditions(this));
	// Needs an refresh
	setNeedsRefresh(true);
	// Refresh
	refresh();
	// Connect slots
	QObject::connect(this, SIGNAL(locationChanged(QString)), SLOT(onLocationChanged()));
	QObject::connect(&s_units, SIGNAL(unitsChanged()), this, SIGNAL(refreshed()));
	// TODO: Add to global list (if there is one)
}

Weather::Location::~Location()
{
	// TODO: Remove from global list (if there is one)
}

void Weather::Location::refresh()
{
	if (location().isEmpty())
		setDisplay(i18nc("@label", "Auto IP"));
	else
		setDisplay(location());
	
	if (coordinates().isEmpty()) {
		setError(true);
		setErrorString("Unable to find location!");
		return;
	}
	
	//setDisplay(coordinates());
	
	setError(false);
	// If the location is known (not IP-based),
	if (!location().isEmpty()) {
		// Load  the data from the cache
		QString error;
		QVariant var = cache()->load(location(), &error);
		
		// If the data is valid,
		if (error.isEmpty() || error.startsWith(OUTDATED_DATA)) {
			qDebug() << "Using location from cache:" << location();
			setData(var.toMap());
			QDateTime lastUpdatedTime = cache()->lastUpdated(location(), &error);
			if (error.isEmpty())
				setLastUpdated(lastUpdatedTime.time());
		}
		
		if (error.isEmpty()) {
			setNeedsRefresh(false);

			QDateTime lastUpdatedTime = cache()->lastUpdated(location(), &error);
			// Request an update at the specified time
			QDateTime then = lastUpdatedTime.addMSecs(refreshTime());
			//qDebug() << "Refresh at:" << then;
			//qDebug() << "Now:" << QDateTime::currentDateTime();
			int time = QDateTime::currentDateTime().msecsTo(then);
			qDebug() << "Needs refresh in" << time/(1000 * 60) << "minutes";
			QTimer::singleShot(time, this, SLOT(timeToRefresh()));
			
			emit refreshed();
			return;
		} else {	
			//if (!error.startsWith(NO_DATA) && !error.startsWith(OUTDATED_DATA)) {
				qWarning("Unable to load data from cache: %s", qPrintable(error));
			//}
		}
	}

	if (hasError() || needsRefresh()) {
		setRefreshing(true);
		qDebug() << "Refreshing...";

		setRefreshing(true);
		service()->download(this);
	} else {
		qDebug() << "No need to refresh!";
	}
}

void Weather::Location::cancelRefresh()
{
	service()->stopJobs(this);
	setRefreshing(false);
}


void Weather::Location::finishRefresh(QVariantMap data, QString error)
{
	qDebug() << "Refresh finished:" << error;
	if (error.isEmpty()) {
		setData(data);
		setLastUpdated(QTime::currentTime());
		setNeedsRefresh(false);
		
		QString internalError;
		if (!location().isEmpty()) {
			cache()->save(location(), &internalError, data);
			if (!internalError.isEmpty()) {
				qWarning("Unable to save location to cache: %s", qPrintable(internalError));
			}
		}

		qDebug() << "Needs refresh in" << refreshTime()/60000 << "minutes";
		QTimer::singleShot(refreshTime(), this, SLOT(timeToRefresh()));
	} else {
		qDebug() << error;
		setError(true);
		setErrorString(error);
	}
	
	qDebug() << "Emitting finished!";
	setRefreshing(false);
	emit refreshed();
}


/*
 * Called by the timer when it is time to refresh again.
 */
void Weather::Location::timeToRefresh()
{
	qDebug() << "Time to refresh!";
	setNeedsRefresh(true);
	if (autoRefresh()) {
		refresh();
	}
}

		
/**
 * Called when the location changed to handle refreshing.
 */
void Weather::Location::onLocationChanged()
{
	timeToRefresh();
	
	if (!autoRefresh()) {
		refresh();
	}
}

	
#include "weather/location.moc"
