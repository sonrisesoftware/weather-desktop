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


#include "forecast/forecast.h"
#include "forecast/weatherpoint.h"
#include "forecast/weatherblock.h"
#include "forecast/datapoint.h"
#include "forecast/alertslist.h"

#include "weather/location.h"

#include <QString>

QString units(const QString& units) {
	if (Weather::Location::html()) {
		return "<sup>" + units + "</sup>";
	} else {
		return units;
	}
}

Forecast::Forecast::Forecast(QObject* parent): Service(parent)
{
	setObjectName("Forecast.io");
}

Forecast::Forecast::~Forecast()
{
	
}

QString Forecast::Forecast::internalLocation(Weather::Location *location)
{
	return location->coordinates();
}

void Forecast::Forecast::download(Weather::Location* location)
{
	json_query(location, "forecast", "", this, SLOT(onWeatherDownloaded(Weather::Location*,QString,QVariantMap)));
}

Weather::DataPoint* Forecast::Forecast::create_conditions(Weather::Location* location)
{
	return new WeatherPoint(location, "currently");
}

Weather::DataBlock* Forecast::Forecast::create_dailyForecast(Weather::Location* location)
{
	return new WeatherBlock(location, "daily");
}

Weather::DataBlock* Forecast::Forecast::create_hourlyForecast(Weather::Location* location)
{
	return new WeatherBlock(location, "hourly");
}

Weather::ManagedList* Forecast::Forecast::create_alerts(Weather::Location* location)
{
	return new AlertsList(location);
}

void Forecast::Forecast::json_query(Weather::Location* location, const QString& query, const QString& params, QObject* receiver, const char* slot)
{
	json_call(location, query + '/' + Weather::Service::apiKey() + '/' + internalLocation(location) + '?' + params, receiver, slot);
}

void Forecast::Forecast::onWeatherDownloaded(Weather::Location* location, QString error, const QVariantMap& data)
{
	if (data["response"].toMap().contains("error")) {
		//error = "[" + data["response"].toMap()["error"].toMap()["type"].toString() + "] " + 
		//		data["response"].toMap()["error"].toMap()["description"].toString();
		error = data["response"].toMap()["error"].toMap()["description"].toString();
	}
	
	location->finishRefresh(data, error);
	emit refreshed();
}


// ##### STATIC CONVERSION METHODS #####

QString Forecast::Forecast::temp(float value) {
	if (Weather::Location::units()->temp() == Weather::Units::Fahrenheit) {
		return validate(value, format(value, 2) + units(TEMP_F));
	} else if (Weather::Location::units()->temp() == Weather::Units::Celsius) {
		return validate(value, format(5.0/9.0 * (value - 32), 2) + units(TEMP_C));
	} else {
		qFatal("Unknown units!");
		return "";
	}
}

QString Forecast::Forecast::clouds(float value) {
	//0 corresponds to clear sky, 0.4 to scattered clouds, 0.75 to broken cloud cover, and 1 to completely overcast skies.
	QString weather = "Clear";
	if (value > 0.3) weather = "Scattered";
	if (value > 0.6) weather = "Broken";
	if (value > 0.9) weather = "Overcast";
	
	return validate(value, weather/*,format(value * 100) + '%'*/);
}

QString Forecast::Forecast::humidity(float value) {
	return validate(value, format(value * 100) + '%');
}

QString Forecast::Forecast::probability(float value) {
	return validate(value, format(value * 100, 2) + '%');
}

QString Forecast::Forecast::wind(float speed, float dir) {
	QString from = "";
	QString color = "";
	QString desc = "";
	
	if (dir != -99) {	
		static QString compass[] = {
			"N", "NE", "E", "SE", "S", "SW", "W", "NW", "N"
		};
		
		/*static QString compass[] = {
		*	"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW", "N"
	};*/
		float index = dir * ((float) ((sizeof(compass)/sizeof(compass[0])) - 1))/360;
		int i = (int) index;
		if (index - i >= 0.5)
			i++;
		
		if (speed > 25) {
			color = "#ffec2f"; // 25-31 mph		Strong Breeze
			desc = "Strong Breeze";
		}
		if (speed > 32) {
			color = "#f98b20"; // 32-38 mph		Near Gale
			desc = "Near Gale";
		}
		if (speed > 39) {
			color = "#c31f1f"; // 39 mph		Gale
			desc = "Gale";
		}
		
		from = compass[i] + " @ ";
	}
	QString wind;
	if (Weather::Location::units()->speed() == Weather::Units::MilesPerHour) {
		wind = validate(speed, from + format(speed) + " mph");
	} else if (Weather::Location::units()->speed() == Weather::Units::KilometersPerHour) {
		wind = validate(speed, from + format(1.60934 * speed) + " km/hr");
	} else if (Weather::Location::units()->speed() == Weather::Units::MetersPerSecond) {
		wind = validate(speed, from + format(0.44704 * speed) + " m/s");
	} else {
		qFatal("Unknown units!");
		return "";
	}
	
	if (!color.isEmpty() && !wind.isEmpty()) {
		return "<font color=\"" + color + "\">" + wind + "</font>";
	} else {
		return wind;
	}
}

QString Forecast::Forecast::pressure(float value) {
	if (Weather::Location::units()->pressure() == Weather::Units::InchesMercury) {
		return validate(value, format(0.02953 * value, 4) + " inHg");
	} else if (Weather::Location::units()->pressure() == Weather::Units::Millibars) {
		return validate(value, format(value, 4) + " millibars");
	} else {
		qFatal("Unknown units!");
		return "";
	}
}

QString Forecast::Forecast::visibility(float value) {
	if (Weather::Location::units()->longDistance() == Weather::Units::Miles) {
		return validate(value, format(value) + " mi");
	} else if (Weather::Location::units()->longDistance() == Weather::Units::Kilometers) {
		return validate(value, format(1.60934 * value) + " km");
	} else {
		qFatal("Unknown units!");
		return "";
	}
}

KIcon Forecast::Forecast::icon(QString name) {
	QString code = "weather-desktop";
	
	if (name == "clear-day") {
		code = "weather-clear";
	} else if (name == "clear-night") {
		code = "weather-clear-night";
	} else if (name == "rain") {
		code = "weather-showers";
	} else if (name == "snow") {
		code = "weather-snow";
	} else if (name == "sleet") {
		code = "weather-freezing-rain";
	} else if (name == "wind") {
		//TODO: Add missing icon!
	} else if (name == "fog") {
		code = "weather-mist";
	} else if (name == "cloudy") {
		code = "weather-many-clouds";
	} else if (name == "partly-cloudy-day") {
		code = "weather-clouds";
	} else if (name == "partly-cloudy-night") {
		code = "weather-clouds-night";
	}
	
	return KIcon(code);
}

QString Forecast::Forecast::precip(Point* data)
{
	QString color = "";
	QString weather = "Light ";
	if (data->precipIntensity() > 0.017) { weather = ""; }
	if (data->precipIntensity() > 0.4)  { weather = "Moderate "; color = "#ffec2f"; }
	if (data->precipIntensity() > 0.8) { weather = "Heavy "; color = "#c31f1f"; }

	if (!data->precipType().isEmpty()) {
		if (weather.isEmpty()) {
			weather = data->precipType()[0].toUpper() + data->precipType().right(data->precipType().length() - 1);
		} else {
			weather += data->precipType();
		}
	}
	
	if (Weather::Location::html() && !color.isEmpty()) {
		weather = "<font color=\"" + color + "\">" + weather + "</font>";
	}
	
	return weather == "Light " ? "None" : weather;
}

#include "forecast/forecast.moc"

