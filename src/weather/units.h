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


#ifndef WEATHER_UNITS_H
#define WEATHER_UNITS_H

#include <QObject>


namespace Weather {

	class Units: public QObject {
		Q_OBJECT
		
		Q_PROPERTY(System system READ system WRITE setSystem NOTIFY systemChanged)
		
		Q_PROPERTY(Temperature temp READ temp WRITE setTemp NOTIFY tempChanged)
		Q_PROPERTY(Pressure pressure READ pressure WRITE setPressure NOTIFY pressureChanged)
		Q_PROPERTY(Speed speed READ speed WRITE setSpeed NOTIFY speedChanged)
		Q_PROPERTY(Distance shortDistance READ shortDistance WRITE setShortDistance NOTIFY shortDistanceChanged)
		Q_PROPERTY(Distance longDistance READ longDistance WRITE setLongDistance NOTIFY longDistanceChanged)
		
	public:
		enum Temperature {
			Celsius,
			Fahrenheit
		};
		
		enum Pressure {
			Millibars,
			InchesMercury
		};
		
		enum Speed {
			MilesPerHour,
			MetersPerSecond,
			KilometersPerHour
		};
		
		enum Distance {
			Miles,
			Feet,
			Kilometers,
			Meters
		};
		
		enum System {
			English,
			Metric
		};
		
		Units(System system, QObject* parent = 0);
		Units(const Units& other);
		Units& operator=(const Units& units);
		virtual ~Units();
		
	private slots:
		void onSystemChanged();
		
	signals:
		void unitsChanged();
		
	#include "weather/units.gen"
	};

}

#endif // WEATHER_UNITS_H
