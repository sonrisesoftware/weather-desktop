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


#include "forecast/weatherpoint.h"

#include "forecast/forecast.h"
#include "forecast/datapoint.h"
#include "forecast/datablock.h"

#include "weather/datapoint.h"
#include "weather/location.h"

//using namespace Forecast;

Forecast::WeatherPoint::WeatherPoint(Weather::Location* location, const QString& path): Weather::DataPoint(location, path)
{
	setData(new Point(location, path));
}

Forecast::WeatherPoint::WeatherPoint(Weather::Location* location, Point *data): Weather::DataPoint(location, data->path())
{
	setData(data);
}

Forecast::WeatherPoint::~WeatherPoint()
{

}

void Forecast::WeatherPoint::refresh()
{
	if (location()->hasError()) return;
	
	data()->load();
	
	setTime(data()->time());
	setIcon(Forecast::Forecast::icon(data()->icon()));
	setSummary(data()->summary());
	setCloudCover(Forecast::Forecast::clouds(data()->cloudCover()));
	setDewPoint(Forecast::Forecast::temp(data()->dewPoint()));
	setHumidity(Forecast::Forecast::humidity(data()->humidity()));
	setWind(Forecast::Forecast::wind(data()->windSpeed(), data()->windBearing()));
	setTemperature(Forecast::Forecast::temp(data()->temperature()));
	setTemperatureMin(Forecast::Forecast::temp(data()->temperatureMin()));
	setTemperatureMax(Forecast::Forecast::temp(data()->temperatureMax()));
	setPressure(Forecast::Forecast::pressure(data()->pressure()));
	setVisibility(Forecast::Forecast::visibility(data()->visibility()));
	setPrecip(Forecast::Forecast::precip(data()));
	setPrecipProbability(Forecast::Forecast::probability(data()->precipProbability()));
	
	updateColor(data()->temperature());
	
// 	Q_PROPERTY(QDateTime sunrise READ sunrise WRITE setSunrise NOTIFY sunriseChanged);
// 	Q_PROPERTY(QDateTime sunset READ sunset WRITE setSunset NOTIFY sunsetChanged);
// 	
// 	Q_PROPERTY(QString precipAccumulation READ precipAccumulation WRITE setPrecipAccumulation NOTIFY precipAccumulationChanged);
// 	
// 	Q_PROPERTY(QString feelsLike READ feelsLike NOTIFY feelsLikeChanged)
// 	Q_PROPERTY(QString windGust READ windGust NOTIFY windGustChanged)
// 	
// 	Q_PROPERTY(QString ozone READ ozone WRITE setOzone NOTIFY ozoneChanged);
}


#include "forecast/weatherpoint.moc"
