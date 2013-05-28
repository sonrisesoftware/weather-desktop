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
	setObjectName(path);
}

Point::~Point()
{

}

void Point::load()
{
	if (location()->hasError()) return;
	
	setTime(QDateTime());
	setSummary("");
	setIcon("");
	
	setSunriseTime(QDateTime());
	setSunsetTime(QDateTime());
	
	setPrecipIntensity(-99);
	setPrecipIntensityMax(-99);
	setPrecipIntensityMaxTime(QDateTime());
	setPrecipProbability(-99);
	setPrecipType("");
	setPrecipAccumulation(-99);
	
	setTemperature(-99);
	setTemperatureMin(-99);
	setTemperatureMinTime(QDateTime());
	setTemperatureMax(-99);
	setTemperatureMaxTime(QDateTime());

	setDewPoint(-99);
	setWindSpeed(-99);
	setWindBearing(-99);
	setCloudCover(-99);

	setHumidity(-99);
	setPressure(-99);
	setVisibility(-99);
	setOzone(-99);	
	
	QVariantMap data = getJson(location()->data(), path()).toMap();
	
	foreach(const QString& item, data.keys()) {
		Q_ASSERT(item != "location");
		if (property(qPrintable(item)).type() == QVariant::DateTime) {
			// Time properties are represented by the seconds since the UNIX epoch
            setProperty(qPrintable(item), QDateTime::fromMSecsSinceEpoch(data[item].toLongLong() * 1000).toUTC());
		} else {
			//qDebug() << item << "\t" << property(qPrintable(item)).typeName() << "==" << data[item].typeName();
			//Q_ASSERT(property(qPrintable(item)).typeName() == data[item].typeName());
			setProperty(qPrintable(item), data[item]);
		}
		//qDebug() << qPrintable(item) << "\t=" << property(qPrintable(item));
	}
}


#include "forecast/datapoint.moc"
