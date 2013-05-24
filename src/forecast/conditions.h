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


#ifndef FORECAST_CONDITIONS_H
#define FORECAST_CONDITIONS_H

#include "weather/conditions.h"
#include "forecast/datapoint.h"

namespace Forecast {

	class ForecastConditions : public Weather::Conditions
	{
		Q_OBJECT
		Q_PROPERTY(DataPoint *data READ data NOTIFY dataChanged)

	public:
		explicit ForecastConditions(Weather::Location* location);
		virtual ~ForecastConditions();
		
		virtual void refresh();
		
	#include "forecast/conditions.gen"
	};

}

#endif // FORECAST_CONDITIONS_H
