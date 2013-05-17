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


#ifndef APPLICATION_H
#define APPLICATION_H

#include <KDE/KApplication>
#include <KDE/KMainWindow>

#include <QDeclarativeEngine>
#include "weather-desktop.h"
#include "weather/service.h"

class Application : public KApplication
{
	Q_OBJECT
	
	Q_PROPERTY(Weather::Service *service READ service WRITE setService NOTIFY serviceChanged)

public:
	Application();
    virtual ~Application();
	
	static void setupDeclarativeBindings(QDeclarativeEngine* declarativeEngine);
	
	static KMainWindow *window() {
		return m_window;
	}
	
	static void setWindow(KMainWindow *window) {
		Q_ASSERT(m_window == nullptr);
		m_window = window;
	}
	
	static void error(const QString& msg, const QString& error);
	static void error(const QString& msg);
	
private:
	void registerQMLTypes();
	
	static KMainWindow *m_window;
	
#include "application.gen"
};

#endif // APPLICATION_H
