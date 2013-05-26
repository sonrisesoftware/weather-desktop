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

#include "forecast/datablock.h"

#include "main.h"
#include "weather/location.h"
#include "forecast/datapoint.h"

using namespace Forecast;

Block::Block(Weather::Location *location, const QString& path): QObject(location)
{
	Q_ASSERT(location != nullptr);
	setLocation(location);
	setPath(path);
}

Block::~Block()
{

}

void Block::load()
{
	if (location()->hasError()) return;
	
	QVariantMap data = getJson(location()->data(), path()).toMap();
	
	QVariantList list = data["data"].toList();
			
	while (!this->data().isEmpty()) {
		this->data().takeFirst()->deleteLater();
	}
	
	for (int i = 0; i < list.length(); i++) {
		Point *point = new Point(location(), path() + ".data." + QString::number(i));
		point->load();
		this->data().append(point);
	}
	
	setSummary(data["summary"].toString());
	setIcon(data["icon"].toString());
}


#include "forecast/datablock.moc"
