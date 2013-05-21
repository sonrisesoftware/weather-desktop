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


#ifndef FORECASTIO_CONDITIONS_H
#define FORECASTIO_CONDITIONS_H

#include "weather/conditions.h"

namespace ForecastIO {

	class ForecastIOConditions : public Weather::Conditions
	{
		Q_OBJECT

	public:
		explicit ForecastIOConditions(Weather::Location* location);
		virtual ~ForecastIOConditions();
		
		virtual void refresh();
		
	#include "forecast.io/conditions.gen"
	};

}

#endif // FORECASTIO_CONDITIONS_H
