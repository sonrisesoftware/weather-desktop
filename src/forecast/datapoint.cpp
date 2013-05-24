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
#include <weather/location.h>

using namespace Forecast;

DataPoint::DataPoint(Weather::Location *location, const QString& path): QObject(location)
{
	Q_ASSERT(location != nullptr);
	setLocation(location);
	setPath(path);
}

DataPoint::~DataPoint()
{

}

void DataPoint::load()
{
	if (location()->hasError()) return;
	
	qDebug() << "Loading:" << path();
	
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
		//qDebug() << qPrintable(item) << "\t=" << property(qPrintable(item));
	}
}


#include "forecast/datapoint.moc"
