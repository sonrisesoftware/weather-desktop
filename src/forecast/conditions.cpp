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


#include "forecast/conditions.h"
#include "forecast/forecast.h"

using namespace Forecast;

ForecastConditions::ForecastConditions(Weather::Location* location): Weather::Conditions(location)
{
	setData(new DataPoint(location, "currently"));
}

ForecastConditions::~ForecastConditions()
{
}

void ForecastConditions::refresh()
{
	if (location()->hasError()) return;
	
	data()->load();
	
	location()->setDay(QDateTime::currentDateTime() > data()->sunrise() && QDateTime::currentDateTime() < data()->sunset());
	
	setIcon(Forecast::Forecast::icon(data()->icon()));
	setWeather(data()->summary());
	setClouds(Forecast::Forecast::clouds(data()->cloudCover()));
	setDewpoint(Forecast::Forecast::temp(data()->dewPoint()));
	setHumidity(Forecast::Forecast::humidity(data()->humidity()));
	setWind(Forecast::Forecast::wind(data()->windSpeed(), data()->windBearing()));
	setTemp(Forecast::Forecast::temp(data()->temperature()));
	setPressure(Forecast::Forecast::pressure(data()->pressure()));
	setVisibility(Forecast::Forecast::visibility(data()->visibility()));
	setPrecip(Forecast::Forecast::precip(data()));
}

#include "forecast/conditions.moc"
