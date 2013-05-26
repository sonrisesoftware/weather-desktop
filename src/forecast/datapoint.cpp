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


#include "forecast/datapoint.h"

#include "weather/location.h"

using namespace Forecast;

Point::Point(Weather::Location *location, const QString& path): QObject(location)
{
	Q_ASSERT(location != nullptr);
	setLocation(location);
	setPath(path);
}

Point::~Point()
{

}

void Point::load()
{
	if (location()->hasError()) return;
	
	qDebug() << "Loading:" << path();
	
	setTime(QDateTime());
	setSummary("");
	setIcon("");
	
	setSunrise(QDateTime());
	setSunset(QDateTime());
	
	setPrecipIntensity(0);
	setPrecipIntensityMax(0);
	setPrecipIntensityMaxTime(QDateTime());
	setPrecipProbability(0);
// 	Q_PROPERTY(QString precipType READ precipType WRITE setPrecipType NOTIFY precipTypeChanged);
// 	Q_PROPERTY(float precipAccumulation READ precipAccumulation WRITE setTrecipAccumulation NOTIFY precipAccumulationChanged);
// 	
// 	Q_PROPERTY(float temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged);
// 	Q_PROPERTY(float temperatureMin READ temperatureMin WRITE setTemperatureMin NOTIFY temperatureMinChanged);
// 	Q_PROPERTY(QDateTime temperatureMinTime READ temperatureMinTime WRITE setTemperatureMinTime NOTIFY temperatureMinTimeChanged);
// 	Q_PROPERTY(float temperatureMax READ temperatureMax WRITE setTemperatureMax NOTIFY temperatureMaxChanged);
// 	Q_PROPERTY(QDateTime temperatureMaxTime READ temperatureMaxTime WRITE setTemperatureMaxTime NOTIFY temperatureMaxTimeChanged);
// 	
// 	Q_PROPERTY(float dewPoint READ dewPoint WRITE setDewPoint NOTIFY dewPointChanged);
// 	Q_PROPERTY(float windSpeed READ windSpeed WRITE setWindSpeed NOTIFY windSpeedChanged);
// 	Q_PROPERTY(float windBearing READ windBearing WRITE setSindBearing NOTIFY windBearingChanged);
// 	Q_PROPERTY(float cloudCover READ cloudCover WRITE setCloudCover NOTIFY cloudCoverChanged);
// 	
// 	Q_PROPERTY(float humidity READ humidity WRITE setHumidity NOTIFY humidityChanged);
// 	Q_PROPERTY(float pressure READ pressure WRITE setPressure NOTIFY pressureChanged);
// 	Q_PROPERTY(float visibility READ visibility WRITE setVisibility NOTIFY visibilityChanged);
// 	Q_PROPERTY(float ozone READ ozone WRITE setOzone NOTIFY ozoneChanged);
	
	
	QVariantMap data = getJson(location()->data(), path()).toMap();
	
	foreach(const QString& item, data.keys()) {
		if (property(qPrintable(item)).type() == QVariant::DateTime) {
			// Time properties are represented by the seconds since the UNIX epoch
            setProperty(qPrintable(item), QDateTime::fromMSecsSinceEpoch(data[item].toLongLong() * 1000).toUTC());
		} else {
			//qDebug() << item << "\t" << property(qPrintable(item)).typeName() << "==" << data[item].typeName();
			//Q_ASSERT(property(qPrintable(item)).typeName() == data[item].typeName());
			setProperty(qPrintable(item), data[item]);
		}
		qDebug() << qPrintable(item) << "\t=" << property(qPrintable(item));
	}
}


#include "forecast/datapoint.moc"
