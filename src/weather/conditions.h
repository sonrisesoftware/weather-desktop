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


#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "weather/service.h"
#include "weather/location.h"

#include <QObject>
#include <QColor>
#include <QIcon>

namespace Weather
{
	class Location;
	
	class Conditions: public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(QString temp READ temp NOTIFY tempChanged)
		Q_PROPERTY(QString windchill READ windchill NOTIFY windchillChanged)
		Q_PROPERTY(QString dewpoint READ dewpoint NOTIFY dewpointChanged)
		Q_PROPERTY(QString weather READ weather NOTIFY weatherChanged)
		Q_PROPERTY(QString pressure READ pressure NOTIFY pressureChanged)
		Q_PROPERTY(QString visibility READ visibility NOTIFY visibilityChanged);
		Q_PROPERTY(QString clouds READ clouds NOTIFY cloudsChanged)
		
		Q_PROPERTY(QString wind READ wind NOTIFY windChanged)
		Q_PROPERTY(QString windgust READ windgust NOTIFY windgustChanged)
		
		Q_PROPERTY(QString humidity READ humidity NOTIFY humidityChanged)
		Q_PROPERTY(QString precip READ precip NOTIFY precipChanged)
		
		Q_PROPERTY(QIcon icon READ icon NOTIFY iconChanged)
		Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
		
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged)

	public:
		explicit Conditions(Weather::Location *location);
		virtual ~Conditions();
		
	public slots:
		virtual void refresh() = 0;
		
	signals:
		void refreshed();
		
	private slots:
		void updateColor(const QString& temp);
		
	#include "weather/conditions.gen"
	};
}

#endif // CONDITIONS_H
