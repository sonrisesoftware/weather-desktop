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
#include "weather-desktop.h"
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
	
	m_autoLocation = new Weather::Location(this);
	setCurrentLocation(autoLocation());
	loadSettings();
	
	m_view = new QDeclarativeView(this);
	m_view->rootContext()->setContextProperty("WeatherApp", this);
	QObject::connect(m_view->engine(), SIGNAL(quit()), this, SLOT(test()));
	m_view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	m_view->engine()->addImportPath("/usr/lib/kde4/imports");
	m_view->setSource(RESOURCE("qml/main.qml"));
	Q_ASSERT(m_view->errors().length() == 0); // Check for errors in the qml file
	
	QDeclarativeProperty(m_view->rootObject(), "implicitWidth").connectNotifySignal(this, SLOT(onImplicitWidthChanged()));
	QDeclarativeProperty(m_view->rootObject(), "implicitHeight").connectNotifySignal(this, SLOT(onImplicitHeightChanged()));
	onImplicitWidthChanged();
	onImplicitHeightChanged();
	
	setCentralWidget(m_view);
	
	menuBar()->setHidden(true);
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
	delete currentLocation();
	setCurrentLocation(new Weather::Location("Home", "St. Clair, MO", this));
}

void WeatherDesktop::loadSettings()
{
	foreach(QString str, Settings::locations()) {
		QStringList list = str.split(":");
		Q_ASSERT(list.length() == 2);
		addLocation(list[0], list[1]);
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

#include "weather-desktop.moc"
