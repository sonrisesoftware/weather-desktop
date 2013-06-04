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


#include "alert.h"
#include "weather/location.h"

using namespace Forecast;

Alert::Alert(Weather::Location* location, const QString& path): Weather::Alert(location)
{
	setPath(path);
}

Alert::~Alert()
{

}

void Alert::refresh()
{
	if (location()->hasError()) return;
	
	QVariantMap data = getJson(location()->data(), path()).toMap();
	
	setTitle(getJson(data, "title").toString());
	setUrl(getJson(data, "uri").toUrl());
	setExpires(QDateTime::fromMSecsSinceEpoch(getJson(data, "expires").toLongLong() * 1000).toUTC());
}


#include "forecast/alert.moc"
