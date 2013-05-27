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


#include "weather/datapoint.h"

#include "weather/location.h"
#include "main.h"
#include <QFile>

using namespace Weather;

DataPoint::DataPoint(Weather::Location *location, const QString& path): QObject(location)
{
	Q_ASSERT(location != nullptr);
	setLocation(location);
	setPath(path);
	
	QObject::connect(location, SIGNAL(refreshed()), this, SLOT(refresh()));
	QObject::connect(this, SIGNAL(iconChanged(QIcon)), this, SLOT(onIconChanged(QIcon)));
}

DataPoint::~DataPoint()
{

}

void DataPoint::updateColor(float temp)
{

}

void Weather::DataPoint::onIconChanged(const QIcon& icon)
{
	QString fileName = RESOURCE_FILE("images/" + icon.name());
	
	if (!QFile(fileName).exists()) {
		fileName = RESOURCE_FILE("images/weather-clear.jpg");
	}
	
	setImage(fileName);
}


#include "weather/datapoint.moc"
