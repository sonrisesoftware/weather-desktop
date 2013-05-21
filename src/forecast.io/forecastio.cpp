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


#include "forecast.io/forecastio.h"
#include "forecast.io/conditions.h"

ForecastIO::ForecastIO::ForecastIO(QObject* parent): Service(parent)
{
	
}

ForecastIO::ForecastIO::~ForecastIO()
{
	
}

QString ForecastIO::ForecastIO::internalLocation(Weather::Location *location)
{
	return "0,0";
}

void ForecastIO::ForecastIO::download(Weather::Location* location)
{
	json_query(location, "forecast", "", this, SLOT(onWeatherDownloaded(Weather::Location*,QString,QVariantMap)));
}

Weather::Conditions* ForecastIO::ForecastIO::create_conditions(Weather::Location* location)
{
	return new ForecastIOConditions(location);
}

void ForecastIO::ForecastIO::json_query(Weather::Location* location, const QString& query, const QString& params, QObject* receiver, const char* slot)
{
	json_call(location, query + '/' + Weather::Service::apiKey() + '/' + internalLocation(location) + '?' + params, receiver, slot);
}

void ForecastIO::ForecastIO::onWeatherDownloaded(Weather::Location* location, QString error, const QVariantMap& data)
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


#include "forecast.io/forecastio.moc"