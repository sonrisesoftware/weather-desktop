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

#include "main.h"
#include "forecast/datablock.h"

using namespace Forecast;

DataBlock::DataBlock(Weather::Location *location, const QString& path): QObject(location)
{
	Q_ASSERT(location != nullptr);
	setLocation(location);
	setPath(path);
}

DataBlock::~DataBlock()
{

}

void DataBlock::load()
{
	if (location()->hasError()) return;
	
	qDebug() << "Loading...";
	
	QVariantMap data = getJson(location()->data(), path()).toMap();
	
	foreach(const QString& item, data.keys()) {
		if (item == "data") {
			QVariantList list = data[item].toList();
			
			while (!this->data().isEmpty()) {
				delete this->data().takeFirst();
			}
			
			for (int i = 0; i < list.length(); i++) {
				DataPoint *point = new DataPoint(location(), path() + ".data." + QString::number(i));
				point->load();
				this->data().append(point);
			}
		} else if (property(qPrintable(item)).type() == QVariant::DateTime) {
			// Time properties are represented by the seconds since the UNIX epoch
			setProperty(qPrintable(item), QDateTime::fromMSecsSinceEpoch(data[item].toLongLong() * 1000).toUTC());
		} else {
			//qDebug() << item << "\t" << property(qPrintable(item)).typeName() << "==" << data[item].typeName();
			//Q_ASSERT(property(qPrintable(item)).typeName() == data[item].typeName());
			setProperty(qPrintable(item), data[item]);
		}
		//qDebug() << qPrintable(item) << "\t=" << property(qPrintable(item));
	}
	
	qDebug() << "Summary:" << summary();
	qDebug() << "Icon:" << icon();
	qDebug() << "Data:" << this->data();
}


#include "forecast/datablock.moc"
