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


#include "forecast.io/datapoint.h"
#include <weather/location.h>

using namespace Forecast;

QVariant get(const QVariantMap& data, const QString& path) {
	QStringList list = path.split('.');
	QVariant result = data;
	
	foreach (const QString& item, list) {		
		if (result.type() == QVariant::List) {
			result = result.toList()[item.toInt()];
		} else if (result.type() == QVariant::Map) {
			result = result.toMap()[item];
		} else {
			qFatal(qPrintable("Invalid type in path: " + result.type()));
		}
		
		Q_ASSERT(!result.isNull());
	}
	
	return result;
}

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
	
	QVariantMap data = get(location()->data(), path()).toMap();
	
	foreach(const QString& item, data.keys()) {
		if (property(qPrintable(item)).type() == QVariant::DateTime) {
			// Time properties are represented by the seconds since the UNIX epoch
            setProperty(qPrintable(item), QDateTime::fromMSecsSinceEpoch(data[item].toLongLong() * 1000).toUTC());
		} else {
			setProperty(qPrintable(item), data[item]);
		}
		qDebug() << qPrintable(item) << "\t=" << property(qPrintable(item));
	}
}


#include "forecast.io/datapoint.moc"
