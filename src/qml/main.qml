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

import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.graphicswidgets 0.1 as PlasmaWidgets

Rectangle {
	id: root
	
	property variant appStyle: Style {
		id: style
	}
	
	/*Image {
		id: background
		//source: "images/background.jpg"
		source: "images/weather-clear.jpg"
		anchors.fill: parent
	}*/
	
	Grid {
		anchors {
			fill: root
			leftMargin: 20
			rightMargin: 20
			topMargin: 20
			bottomMargin: 20
		}
		
		spacing: 20		
		
		Repeater {
			model: WeatherApp.locationNames.length

			delegate: WeatherTile {
				title: WeatherApp.location(modelData).name;
				icon: WeatherApp.location(modelData).conditions.icon;
				weather: WeatherApp.location(modelData).conditions.weather;
				temp: WeatherApp.location(modelData).conditions.temp;
			}
		}
	}
}
