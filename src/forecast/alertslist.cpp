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


#include "forecast/alertslist.h"

#include "forecast/alert.h"
#include "weather/location.h"

using namespace Forecast;

AlertsList::AlertsList(Weather::Location *location): ManagedList(location)
{
	Q_ASSERT(location != nullptr);
	
	setLocation(location);
	QObject::connect(location, SIGNAL(refreshed()), this, SLOT(refresh()));
}

AlertsList::~AlertsList()
{
	
}

void AlertsList::refresh()
{
	if (location()->hasError()) return;
	
	QVariantList data = getJson(location()->data(), "alerts").toList();
	
	while (data.length() < items().length()) {
		items().takeLast()->deleteLater();
	}
	
	while (data.length() > items().length()) {
		Forecast::Alert *alert = new Forecast::Alert(location(), "alerts." + QString::number(items().length()));
		alert->refresh();
		items().append(alert);
	}
	
	setLength(items().length());
	emit itemsChanged(items());
}

#include "forecast/alertslist.moc"
