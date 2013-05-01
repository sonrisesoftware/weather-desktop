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


#include "worldweather/worldweatheronline.h"
#include "worldweather/conditions.h"

WorldWeatherOnline::WorldWeatherOnline::WorldWeatherOnline(Weather::Location* location): Weather::Service(location)
{
	qDebug() << "WorldWeatherOnline service!";
	setLocation(location);
}

QString WorldWeatherOnline::WorldWeatherOnline::prefix()
{
    return "http://api.worldweatheronline.com/free/v1/";
}

Weather::Conditions* WorldWeatherOnline::WorldWeatherOnline::create_conditions()
{
	qDebug() << "Creating conditions for WWO";
	return new WorldWeatherConditions(location());
}

QVariantMap WorldWeatherOnline::WorldWeatherOnline::json_query(QString* error, const QString& query, const QString& params)
{
	QVariantMap map = json_call(error, query + ".ashx?q=" + internalLocation() + "&format=json&" + params + "&key=" + Weather::Service::apiKey());
	if (map["data"].toMap().contains("error")) {
		qDebug() << "ERROR!";
		*error = map["data"].toMap()["error"].toList()[0].toMap()["msg"].toString();
	}
	
	return map;
}

QString WorldWeatherOnline::WorldWeatherOnline::internalLocation()
{
	return location()->location().replace(' ', '+').replace("St.", "Saint");
}

void WorldWeatherOnline::WorldWeatherOnline::refresh()
{
	QString error;
	QVariantMap data = location()->api()->json_query(&error, "weather");
	
	if (!error.isEmpty()) {
		location()->setError(true);
		location()->setErrorMessage(error);
		return;
	}
	
	this->data()["weather"] = data;
}


#include "worldweather/worldweatheronline.moc"