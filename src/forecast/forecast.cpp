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
#include "forecast/conditions.h"

Forecast::Forecast::Forecast(QObject* parent): Service(parent)
{
	
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

Weather::Conditions* Forecast::Forecast::create_conditions(Weather::Location* location)
{
	return new ForecastConditions(location);
}

void Forecast::Forecast::json_query(Weather::Location* location, const QString& query, const QString& params, QObject* receiver, const char* slot)
{
	json_call(location, query + '/' + Weather::Service::apiKey() + '/' + internalLocation(location) + '?' + params, receiver, slot);
}

void Forecast::Forecast::onWeatherDownloaded(Weather::Location* location, QString error, const QVariantMap& data)
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


#include "forecast/forecast.moc"

