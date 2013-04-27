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


#include "worldweather/conditions.h"
#include "weather/service.h"

using namespace WorldWeatherOnline;

WorldWeatherConditions::WorldWeatherConditions(Weather::Location* location): Conditions(location)
{
	qDebug() << "WWO Conditions!";
}

WorldWeatherConditions::~WorldWeatherConditions()
{

}

void WorldWeatherConditions::refresh()
{
	qDebug() << "Refreshing WWO!";
	QString error;
	Q_ASSERT(location() != nullptr);
	Q_ASSERT(location()->api() != nullptr);
	setTemp(location()->api()->json_query(&error, "weather", "")["weather"].toMap()["temp_C"].toString());
}

#include "worldweather/conditions.moc"