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

#include "wunderground/wunderground.h"

#include "main.h"
#include "wunderground/conditions.h"

using namespace Wunderground;

QMap<QString, KIcon> Wunderground::Wunderground::icons_day;
QMap<QString, KIcon> Wunderground::Wunderground::icons_night;
bool Wunderground::Wunderground::s_initialized = false;

Wunderground::Wunderground::Wunderground(QObject *parent): Weather::Service(parent)
{
	if (!s_initialized) {
		init();
		s_initialized = true;
	}
}

Wunderground::Wunderground::~Wunderground()
{

}

QString Wunderground::Wunderground::internalLocation(Weather::Location *location)
{
	if (location->location().isEmpty()) {
		return "autoip";
	} else {
		QStringList list = location->location().split(",");
		if (list.size() == 2) {
			return list.at(1) + '/' + list.at(0);
		} else {
			return location->location();
		}
	}
}

QString Wunderground::Wunderground::prefix()
{
	return "http://api.wunderground.com/api/";
}

void Wunderground::Wunderground::download(Weather::Location *location)
{
	qDebug() << "Downloading:" << location->location();
	json_query(location, "conditions/forecast", "", this, SLOT(onConditionsDownloaded(Weather::Location *,QString,QVariantMap)));
}

Weather::Conditions* Wunderground::Wunderground::create_conditions(Weather::Location *location)
{
	return new WundergroundConditions(location);
}

void Wunderground::Wunderground::json_query(Weather::Location *location, const QString& query, const QString& params, QObject* receiver, const char* slot)
{
	json_call(location, Weather::Service::apiKey() + '/' + query + "/q/" + internalLocation(location) + ".json?" + params, receiver, slot);
}

void Wunderground::Wunderground::onConditionsDownloaded(Weather::Location *location, QString error, const QVariantMap& data)
{	
	qDebug() << "Conditions downloaded!";
	if (data["response"].toMap().contains("error")) {
		//error = "[" + data["response"].toMap()["error"].toMap()["type"].toString() + "] " + 
		//		data["response"].toMap()["error"].toMap()["description"].toString();
		error = data["response"].toMap()["error"].toMap()["description"].toString();
	}
	
	location->finishRefresh(data, error);
	emit refreshed();
}

void Wunderground::Wunderground::init() {
	icons_day["chanceflurries"]				= KIcon("weather-snow-scattered-day"); //***
	icons_day["flurries"]					= KIcon("weather-snow-scattered-day"); //***
	icons_day["chancesnow"]					= KIcon("weather-snow-scattered");
	icons_day["snow"]						= KIcon("weather-snow");
	
	icons_day["chancerain"]					= KIcon("weather-showers-day"); //***
	icons_day["rain"]						= KIcon("weather-showers");
	
	//icons_day["chancesleet"]				= KIcon("weather-freezing-rain");
	//icons_day["sleet"]						= KIcon("weather-freezing-rain");
	
	icons_day["chancesleet"]			= KIcon("weather-snow-rain");
	icons_day["sleet"]						= KIcon("weather-hail");
	
	icons_day["chancetstorms"]		= KIcon("weather-storm-day"); //***
	icons_day["tstorms"]				= KIcon("weather-storm");
	//icons_day["thunderstorms"]				= KIcon("weather-storm");
	
	icons_day["clear"]						= KIcon("weather-clear"); //***
	icons_day["sunny"]						= KIcon("weather-clear"); //***
	icons_day["mostlysunny"]				= KIcon("weather-few-clouds"); //***
	icons_day["partlycloudy"]				= KIcon("weather-few-clouds"); //***
	//icons_day["scatteredclouds"]			= KIcon("weather-clouds"); //***
	icons_day["partlysunny"]				= KIcon("weather-clouds"); //***
	icons_day["mostlycloudy"]				= KIcon("weather-clouds"); //***
	icons_day["cloudy"]						= KIcon("weather-many-clouds");
	//icons_day["overcast"]					= KIcon("weather-many-clouds");
	
	icons_day["fog"]						= KIcon("weather-mist");
	icons_day["hazy"]						= KIcon("weather-mist");
		
	icons_day["unknown"]					= KIcon("weather-none-available");
	
	
	
	
	// ***** NIGHT ICONS ***** //
	icons_night["chanceflurries"]				= KIcon("weather-snow-scattered-night"); //***
	icons_night["flurries"]					= KIcon("weather-snow-scattered-night"); //***
	icons_night["chancesnow"]					= KIcon("weather-snow-scattered");
	icons_night["snow"]						= KIcon("weather-snow");
	
	icons_night["chancerain"]					= KIcon("weather-showers-night"); //***
	icons_night["rain"]						= KIcon("weather-showers");
	
	//icons_night["chancesleet"]				= KIcon("weather-freezing-rain");
	//icons_night["sleet"]						= KIcon("weather-freezing-rain");
	
	icons_night["chancesleet"]			= KIcon("weather-snow-rain");
	icons_night["sleet"]						= KIcon("weather-hail");
	
	icons_night["chancetstorms"]		= KIcon("weather-storm-night"); //***
	icons_night["tstorms"]				= KIcon("weather-storm");
	//icons_night["thunderstorms"]				= KIcon("weather-storm");
	
	icons_night["clear"]						= KIcon("weather-clear-night"); //***
	icons_night["sunny"]						= KIcon("weather-clear-night"); //***
	icons_night["mostlysunny"]				= KIcon("weather-few-clouds-night"); //***
	icons_night["partlycloudy"]				= KIcon("weather-few-clouds-night"); //***
	//icons_night["scatteredclouds"]			= KIcon("weather-clouds"); //***
	icons_night["partlysunny"]				= KIcon("weather-clouds-night"); //***
	icons_night["mostlycloudy"]				= KIcon("weather-clouds-night"); //***
	icons_night["cloudy"]						= KIcon("weather-many-clouds");
	//icons_night["overcast"]					= KIcon("weather-many-clouds");
	
	icons_night["fog"]						= KIcon("weather-mist");
	icons_night["hazy"]						= KIcon("weather-mist");
		
	icons_night["unknown"]					= KIcon("weather-none-available");
}

KIcon Wunderground::Wunderground::icon(const QString &weather, const bool day) {
	if (!Wunderground::icons_day.contains(weather))
		return Wunderground::icons_day.value("unknown");
	
	if (day) {
		return Wunderground::icons_day.value(weather);
	} else {
		return Wunderground::icons_night.value(weather);
	}
}


#include "wunderground/wunderground.moc"
