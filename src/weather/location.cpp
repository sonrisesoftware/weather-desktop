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
#include "weather/service.h"
#include "weather/conditions.h"

#include <QDateTime>
#include <QtConcurrentRun>
#include <qtimer.h>
#include <KLocalizedString>

#include "config.h"

using namespace Weather;

QList<Location *> Location::m_locations;
bool Location::m_autoRefresh;

Location::Location(const QString& name, const QString& location, QObject* parent)
	: QObject(parent)
{
	//qDebug() << "New location: " + name + " - " + (location.isEmpty() ? "Auto-IP" : location);
	
	// Whenever the location is changed, redownload the weather
	QObject::connect(this, SIGNAL(locationChanged(QString)), this, SLOT(timeToUpdate()));
	if (!autoRefresh()) {
		QObject::connect(this, SIGNAL(locationChanged(QString)), this, SLOT(refresh()));
	}
	
	setNeedsUpdate(true);
	setApi(Weather::Service::create(this));
	m_conditions = api()->create_conditions();
	//qDebug() << "Done with conditions.";
	
	setName(name);
	setLocation(location);
	//qDebug() << "Done.";
	
	m_locations.append(this);
}

Location::Location(QObject* parent): Location(i18nc("@title:tab", "Current"), "", parent)
{

}


Location::~Location()
{
	m_locations.removeOne(this);
}

void Location::refresh()
{
	if (!needsUpdate()) {
		qDebug() << "No need to refresh!";
		return;
	}
	
	qDebug() << "Refreshing...";
	setError(false); // Start fresh
	
	if (location().isEmpty())
		setDisplay(i18nc("@label", "Auto IP"));
	else
		setDisplay(location());
	
	setUpdating(true);
	api()->refresh();
}

void Weather::Location::finishedRefresh()
{
	setUpdating(false);
	setNeedsUpdate(false);
	setLastUpdated(QTime::currentTime());
	qDebug() << "Needs refresh in" << UPDATE_TIME/60000 << "minutes";
	QTimer::singleShot(UPDATE_TIME, this, SLOT(timeToUpdate()));
	emit refreshed();
}


void Weather::Location::stopRefresh()
{
	api()->stopJobs();
	setUpdating(false);
}

void Weather::Location::refreshAll()
{
	foreach (Location *location, m_locations) {
		location->refresh();
	}
}

void Weather::Location::stopAllRefresh()
{
	foreach (Location *location, m_locations) {
		location->stopRefresh();
	}
}

void Weather::Location::timeToUpdate()
{
	qDebug() << "Time to update!";
	setNeedsUpdate(true);
	if (autoRefresh()) {
		refresh();
	}
}

#include "weather/location.moc"
