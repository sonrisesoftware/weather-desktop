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
		
		Q_PROPERTY(Weather::Units::Temperature temp READ temp WRITE setTemp NOTIFY tempChanged)
		Q_PROPERTY(Weather::Units::Pressure pressure READ pressure WRITE setPressure NOTIFY pressureChanged)
		Q_PROPERTY(Weather::Units::System system READ system WRITE setSystem NOTIFY systemChanged)
		
	public:
		enum Temperature {
			CELSIUS,
			FAHRENHEIT
		};
		
		enum Pressure {
			MILLIBARS,
			IN_HG
		};
		
		enum Speed {
			MPH,
			M_PER_S,
			KM_PER_HR
		};
		
		enum System {
			ENGLISH,
			METRIC
		};
		
		explicit Units(Weather::Units::System system, QObject* parent = 0);
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
