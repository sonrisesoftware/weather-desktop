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

#include "wunderground/conditions.h"

#include "wunderground/wunderground.h"
#include "weather/conditions.h"

using namespace Wunderground;

WundergroundConditions::WundergroundConditions(Weather::Location* location): Weather::Conditions(location)
{

}

WundergroundConditions::~WundergroundConditions()
{

}

void WundergroundConditions::refresh()
{
	if (location()->hasError()) return;
	
	QVariantMap data = location()->data()["current_observation"].toMap();

	QString country =  data["display_location"].toMap()["country"].toString();
	
	if (country == "US") {
		location()->setDisplay(data["display_location"].toMap()["full"].toString());
	} else {
		location()->setDisplay(data["display_location"].toMap()["city"].toString() + ", " + country);
	}
	
	setIcon(Wunderground::Wunderground::icon(data["icon"].toString(), true));
	setTemp(data["temp_f"].toString() + TEMP_F); // TODO: Unit conversion
	setVisibility(data["visibility_mi"].toString() + " mi");
	setWeather(data["weather"].toString());
	setPressure(data["pressure_mb"].toString() + " millibars"); //TODO: Unit conversion
	//setClouds(data["cloudcover"].toString() + "%");
	setHumidity(data["relative_humidity"].toString());
	setRainfall(data["precip_today_metric"].toString() + " mm"); //TODO: Unit conversion
	setWind(data["wind_mph"].toString() + " mph from the " + data["wind_dir"].toString()); //TODO: Unit conversion
	setWindgust(data["wind_gust_mph"].toString() + " mph");
	setWindchill(data["feelslike_f"].toString() + TEMP_F);
	setDewpoint(data["dewpoint_f"].toString() + TEMP_F);
}


#include "wunderground/conditions.moc"
