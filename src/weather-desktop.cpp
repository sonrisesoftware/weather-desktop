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

#include "main.h"
#include "application.h"
#include "weather-desktop.h"
#include "weather/service.h"
//#include "weather/cache.h"
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

WeatherDesktop::WeatherDesktop()
	: KXmlGuiWindow()
{	
	setupActions();
	
	setupGUI();
	loadSettings();
	
	m_autoLocation = new Weather::Location(this);
	setCurrentLocation(autoLocation());
	
	m_view = new QDeclarativeView(this);
	m_view->rootContext()->setContextProperty("WeatherApp", this);
	m_view->setStyleSheet("background-color: transparent;");
	m_view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	
	Application::setupDeclarativeBindings(m_view->engine());
	QObject::connect(m_view->engine(), SIGNAL(quit()), this, SLOT(test()));
	
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

void WeatherDesktop::test()
{
	//delete currentLocation();
	setCurrentLocation(new Weather::Location("Home", "Saint Louis, MO", this));
}

void WeatherDesktop::loadSettings()
{
	foreach(QString str, Settings::locations()) {
		QStringList list = str.split(":");
		Q_ASSERT(list.length() == 2);
		addLocation(list[0], list[1]);
	}
	
	QStringList list = Settings::accessCount().split(":");
	qDebug() << "List:" << list;
	QDate current = QDate::currentDate();
	QDate lastUsed = QDate::fromString(list[0]);
	qDebug() << current << lastUsed << (lastUsed == current);
	if (current == lastUsed) {
		Weather::Service::setAccessCount(list[1].toInt() + Weather::Service::accessCount());
		qDebug() << "Loading access count:" << Weather::Service::accessCount();
	}
	
	//Weather::Cache::get()->setRecentLocations(Settings::recentLocations());
}

void WeatherDesktop::saveSettings()
{
	QStringList list;
	foreach(Weather::Location *location, locations()) {
		if (location->location().isEmpty()) continue;
		list.append(location->name() + ':' + location->location());
	}
	Settings::setLocations(list);
	
	qDebug() << "Saving access count:" << QDate::currentDate().toString() + ":" + QString::number(Weather::Service::accessCount());
	Settings::setAccessCount(QDate::currentDate().toString() + ":" + QString::number(Weather::Service::accessCount()));
	
	//Settings::setRecentLocations(Weather::Cache::get()->recentLocations());
	
	Settings::self()->writeConfig();
}

Weather::Location *WeatherDesktop::addLocation(const QString& name, const QString& location)
{
	if (location.isEmpty()) return nullptr;
	qDebug() << "Adding location: " + name + " - " + location;
	Weather::Location *l = new Weather::Location(name, location, this);
	locations().append(l);
	return l;
}

void WeatherDesktop::setLocation(const QString& location)
{
	qDebug() << "Set location to:" << location;
	if (location.isEmpty()) {
		setCurrentLocation(autoLocation());
	} else {
		if (searchLocation() == nullptr) {
			setSearchLocation(new Weather::Location("", location, this));
		} else {
			searchLocation()->setLocation(location);
		}
		setCurrentLocation(searchLocation());
	}
}


#include "weather-desktop.moc"
