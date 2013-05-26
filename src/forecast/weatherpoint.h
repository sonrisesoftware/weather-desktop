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


#ifndef FORECAST_WEATHERPOINT_H
#define FORECAST_WEATHERPOINT_H

#include "weather/datapoint.h"
//#include "forecast/datapoint.h"

namespace Forecast {

	class Point;
	
	class WeatherPoint : public Weather::DataPoint
	{
		Q_OBJECT
		
		Q_PROPERTY(Point *data READ data NOTIFY dataChanged)

	public:
		explicit WeatherPoint(Weather::Location* location, const QString& path);
		explicit WeatherPoint(Weather::Location* location, Point *data);
		virtual ~WeatherPoint();
		
		virtual void refresh();
		
	#include "forecast/weatherpoint.gen"
	};

}

#endif // FORECAST_WEATHERPOINT_H
