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
	
	class Conditions: QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(QString temp READ temp NOTIFY tempChanged)
		Q_PROPERTY(QString windchill READ windchill NOTIFY windchillChanged)
		Q_PROPERTY(QString dewpoint READ dewpoint NOTIFY dewpointChanged)
		Q_PROPERTY(QString weather READ weather NOTIFY weatherChanged)
		Q_PROPERTY(QIcon icon READ icon NOTIFY iconChanged)
		Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
		
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged)

	public:
		explicit Conditions(Weather::Location *location);
		virtual ~Conditions();
		
	public slots:
		void refresh();
		
	signals:
		void refreshed();
		
	private slots:
		void updateColor(const QString& temp);
		
	private:
		QString m_weather = "<Weather>";
		
	#include "weather/conditions.gen"
	};
}

#endif // CONDITIONS_H
