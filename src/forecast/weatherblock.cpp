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


#include "forecast/weatherblock.h"

#include "forecast/forecast.h"
#include "forecast/weatherpoint.h"
#include "forecast/datapoint.h"
#include "forecast/datablock.h"
#include "weather/datapoint.h"
#include "weather/location.h"

Forecast::WeatherBlock::WeatherBlock(Weather::Location* location, const QString& path): DataBlock(location, path)
{
	setData(new Block(location, path));
}

Forecast::WeatherBlock::~WeatherBlock()
{

}

void Forecast::WeatherBlock::refresh()
{
	if (location()->hasError()) return;
	
	data()->load();
	
	setSummary(data()->summary());
	setIcon(Forecast::Forecast::icon(data()->icon()));
	
	while (data()->data().length() < items().length()) {
		items().removeLast();
	}
	
	while (data()->data().length() > items().length()) {
		WeatherPoint *dataPoint = new WeatherPoint(location(), data()->data()[items().length()]);
		dataPoint->refresh();
		items().append(dataPoint);
	}
	
	setLength(items().length());
	emit itemsChanged(items());
}

#include "forecast/weatherblock.moc"
