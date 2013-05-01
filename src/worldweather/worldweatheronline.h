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


#ifndef WORLDWEATHERONLINE_H
#define WORLDWEATHERONLINE_H

#include "weather/service.h"
#include "worldweather/conditions.h"

namespace WorldWeatherOnline {
	class WorldWeatherOnline : public Weather::Service
	{
		Q_OBJECT

	public:
		explicit WorldWeatherOnline(Weather::Location* location);
		
		virtual QVariantMap json_query(QString *error, const QString& query, const QString& params = "");
		
		virtual Weather::Conditions *create_conditions();

	protected:
		virtual QString prefix();
		
		virtual QString internalLocation();
		
	#include "worldweather/worldweatheronline.gen"
	};
}

#endif // WORLDWEATHERONLINE_H
