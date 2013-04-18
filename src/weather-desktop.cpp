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

#include <QGraphicsObject>
#include <QDeclarativeEngine>
#include <QDeclarativeProperty>

#include <KDE/KApplication>
#include <KDE/KStandardAction>
#include <KDE/KActionCollection>
#include <KDE/KMenuBar>

WeatherDesktop::WeatherDesktop()
	: KXmlGuiWindow()
{
	setupActions();
	
	setupGUI();
	
	m_view = new QDeclarativeView(this);
	QObject::connect(m_view->engine(), SIGNAL(quit()), kapp, SLOT(quit()));
	m_view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	m_view->setSource(RESOURCE("qml/main.qml"));
	QDeclarativeProperty(m_view->rootObject(), "minWidth").connectNotifySignal(this, SLOT(onMinimumWidthChanged()));
	QDeclarativeProperty(m_view->rootObject(), "minHeight").connectNotifySignal(this, SLOT(onMinimumHeightChanged()));
	onMinimumWidthChanged();
	onMinimumHeightChanged();
	
	setCentralWidget(m_view);
	
	menuBar()->setHidden(true);
}

WeatherDesktop::~WeatherDesktop()
{
	
}

void WeatherDesktop::setupActions()
{
	KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
}

void WeatherDesktop::onMinimumWidthChanged()
{
	m_view->setMinimumWidth(m_view->rootObject()->property("minWidth").toInt());
}

void WeatherDesktop::onMinimumHeightChanged()
{
	m_view->setMinimumHeight(m_view->rootObject()->property("minHeight").toInt());
}



#include "weather-desktop.moc"
