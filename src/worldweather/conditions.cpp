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
#include "worldweather/conditions.h"
#include "worldweather/worldweatheronline.h"
#include "weather/service.h"

using namespace WorldWeatherOnline;

WorldWeatherConditions::WorldWeatherConditions(Weather::Location* location): Conditions(location)
{
	qDebug() << "WWO Conditions!";
}

WorldWeatherConditions::~WorldWeatherConditions()
{

}

void WorldWeatherConditions::refresh()
{
	Weather::Conditions::refresh();
	qDebug() << "Refreshing WWO!";

	if (location()->hasError()) return;
	
	QVariantMap data = location()->api()->data("weather")["data"].toMap()["current_condition"].toList()[0].toMap();
	
	//qDebug() << "List: " << (*location()->api()->data())["data"].toMap();
	//qDebug() << "Data: " << data;
	//return;
	
	setTemp(data["temp_F"].toString()); // TODO: Unit conversion
	setVisibility(data["visibility"].toString() + " mi");
	setWeather(data["weatherDesc"].toList()[0].toMap()["value"].toString());
	setPressure(data["pressure"].toString() + " millibars"); //TODO: Unit conversion
	setClouds(data["cloudcover"].toString() + "%");
	setHumidity(data["humidity"].toString() + "%");
	setRainfall(data["precipMM"].toString() + " mm"); //TODO: Unit conversion
	setWind(data["windspeedMiles"].toString() + " mph from the " + data["winddir16Point"].toString()); //TODO: Unit conversion
}

#include "worldweather/conditions.moc"