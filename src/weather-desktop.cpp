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

#include "weather-desktop.h"

#include "main.h"
#include "application.h"
#include "weather/service.h"
#include "cache.h"
#include "settings.h"

#include <QGraphicsObject>
#include <QDeclarativeEngine>
#include <QDeclarativeProperty>
#include <QDeclarativeContext>
#include <QtDeclarative>

#include <KDE/KApplication>
#include <KDE/KStandardAction>
#include <KDE/KActionCollection>
#include <KDE/KMenuBar>
#include <KDE/KInputDialog>

WeatherDesktop::WeatherDesktop()
	: KXmlGuiWindow()
{	
	setupActions();
	
	setupGUI();
	loadSettings();
	
	if (locations().length() == 0) {
		if (Weather::Location::cache()->recent().length() > 0) {
			setLocation(Weather::Location::cache()->recent()[0]);
		} else {
			//TODO: Set up a home location
			setLocation("St. Louis, MO");
		}
	} else {
		setCurrentLocation(locations()[0]);
	}
	
	m_view = new QDeclarativeView(this);
	m_view->rootContext()->setContextProperty("WeatherApp", this);
	m_view->setStyleSheet("background-color: transparent;");
	m_view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	
	Application::setupDeclarativeBindings(m_view->engine());
	QObject::connect(m_view->engine(), SIGNAL(quit()), kapp, SLOT(quit()));
	
	m_view->setSource(RESOURCE("qml/main.qml"));
	
	Q_ASSERT(m_view->errors().length() == 0); // Check for errors in the qml file
	
	// Bind the minimum size
	QDeclarativeProperty(m_view->rootObject(), "implicitWidth").connectNotifySignal(this, SLOT(onImplicitWidthChanged()));
	QDeclarativeProperty(m_view->rootObject(), "implicitHeight").connectNotifySignal(this, SLOT(onImplicitHeightChanged()));
	onImplicitWidthChanged();
	onImplicitHeightChanged();
	
	setCentralWidget(m_view);
	
	menuBar()->setHidden(true);
	
	Application::setWindow(this);
}

WeatherDesktop::~WeatherDesktop()
{
	saveSettings();
}

void WeatherDesktop::setupActions()
{
	KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
}

void WeatherDesktop::onImplicitWidthChanged()
{
	m_view->setMinimumWidth(m_view->rootObject()->property("implicitWidth").toInt());
}

void WeatherDesktop::onImplicitHeightChanged()
{
	m_view->setMinimumHeight(m_view->rootObject()->property("implicitHeight").toInt());
}

void WeatherDesktop::loadSettings()
{
	foreach(const QString& str, Settings::locations()) {
		QStringList list = str.split(':');
		Q_ASSERT(list.length() == 2);
		addLocation(list[0], list[1]);
	}
	
	QStringList list = Settings::accessCount().split(':');
	QDate current = QDate::currentDate();
	QDate lastUsed = QDate::fromString(list[0]);
	
	if (current == lastUsed) {
		Weather::Service::setAccessCount(list[1].toInt() + Weather::Service::accessCount());
		qDebug() << "Loading access count:" << Weather::Service::accessCount();
	}
}

void WeatherDesktop::saveSettings()
{
	QStringList list;
	foreach(Weather::Location *location, locations()) {
		if (location->location().isEmpty()) continue;
		list.append(location->name() + ':' + location->location());
	}
	Settings::setLocations(list);
	
	qDebug() << "Saving access count:" << QDate::currentDate().toString() + ':' + QString::number(Weather::Service::accessCount());
	Settings::setAccessCount(QDate::currentDate().toString() + ':' + QString::number(Weather::Service::accessCount()));
	
	Settings::self()->writeConfig();
}

Weather::Location *WeatherDesktop::addLocation(const QString& name, const QString& location)
{
	if (location.isEmpty()) return nullptr;
	qDebug() << "Adding location: " + name + " - " + location;
	Weather::Location *l = new Weather::Location(name, location, this);
	locations().append(l);
	locationNames().append(location);
	emit locationsChanged(locations());
	emit locationNamesChanged(locationNames());
	setCurrentLocation(l);
	return l;
}

void WeatherDesktop::addCurrentLocation()
{
	if (location(currentLocation()->location()) != nullptr) return;
	
	bool ok;	
	QString name = KInputDialog::getText(i18n("New Location"),
			i18n("Name for '%1':",currentLocation()->location()), 
			currentLocation()->display(), &ok, this);
	
	if (!ok) return;
	
	addLocation(name, currentLocation()->location());
}

void WeatherDesktop::removeCurrentLocation()
{
	Weather::Location *l = location(currentLocation()->location());
	
	if (l == nullptr) return;
	
	locations().removeOne(l);
	locationNames().removeOne(l->location());
	emit locationsChanged(locations());
	emit locationNamesChanged(locationNames());
	
	if (locations().length() > 0) {
		setCurrentLocation(locations()[0]);
	}
	
	delete l;
}


Weather::Location* WeatherDesktop::location(QString name)
{
	if (locationNames().contains(name)) {
		return locations()[locationNames().indexOf(name)];
	} else {
		return nullptr;
	}
}

Weather::Location* WeatherDesktop::location(int index)
{
	if (index < locationNames().length()) {
		return locations()[index];
	} else {
		return nullptr;
	}
}

void WeatherDesktop::setLocation(const QString& location)
{
	qDebug() << "Set location to:" << location;
	if (location.isEmpty()) {
		//setCurrentLocation(autoLocation());
		return;
	} else {
		Weather::Location *l = this->location(location);
		if (l != nullptr) {
			setCurrentLocation(l);
		} else {		
			if (searchLocation() == nullptr) {
				setSearchLocation(new Weather::Location("", location, this));
			} else if (searchLocation()->location() != location) {
				searchLocation()->setLocation(location);
			}
			setCurrentLocation(searchLocation());
		}
	}
}


#include "weather-desktop.moc"
