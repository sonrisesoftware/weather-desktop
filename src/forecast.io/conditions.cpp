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


#include "conditions.h"

using namespace ForecastIO;

ForecastIOConditions::ForecastIOConditions(Weather::Location* location): Weather::Conditions(location)
{

}

ForecastIOConditions::~ForecastIOConditions()
{
}

void ForecastIOConditions::refresh()
{
	if (location()->hasError()) return;
	
	QVariantMap data = location()->data()["currently"].toMap();
	qDebug() << data;
	
	setWeather(data["summary"].toString());
	setClouds(QVariant(data["cloudCover"].toFloat() * 100).toString() + "%");
	setDewpoint(data["dewPoint"].toString() + TEMP_F);
	setHumidity(QVariant(data["humidity"].toFloat() * 100).toString() + "%");
	setWind(data["windSpeed"].toString() + " mph from " + data["windBearing"].toString() + i18n(DEG));
	setTemp(data["temperature"].toString() + TEMP_F);
	setPressure(data["pressure"].toString() + " millibars");
	setHumidity(QVariant(data["humidity"].toFloat() * 100).toString() + "%");
}

#include "forecast.io/conditions.moc"
