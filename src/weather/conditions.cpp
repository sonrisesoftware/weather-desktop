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
#include "weather/conditions.h"
#include "weather/location.h"
#include <KIcon>

using namespace Weather;

Conditions::Conditions(Weather::Location *location): QObject(location)
{
	qDebug() << "Generic conditions!";
	Q_ASSERT(location != nullptr);
	setLocation(location);
	QObject::connect(location->api(), SIGNAL(refreshed()), this, SLOT(refresh()));
	QObject::connect(this, SIGNAL(tempChanged(QString)), this, SLOT(updateColor(QString)));
}

Conditions::~Conditions()
{

}

void Conditions::refresh()
{
	qDebug() << "Refreshing conditions...";
	
	setIcon(KIcon("weather-clouds"));
	setWeather("Partly Cloudy");	
	setTemp("0");
	
	setWindchill("0");
	setDewpoint("0");
	
	setPressure("29.92 inHg");
	setVisibility("10 mi");
	setClouds("25%");
	
	setWind("5 mph from the North");
	setWindgust("10 mph");
	
	setHumidity("70%");
	setRainfall("0.5 in");
	setSnowdepth("N/A");
}

void Weather::Conditions::updateColor(const QString& temp)
{
	qDebug() << "Updating color...";
}


#include "weather/conditions.moc"