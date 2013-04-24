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
//import org.kde.plasma.graphicswidgets 0.1 as PlasmaWidgets
import org.kde.qtextracomponents 0.1

import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents

Rectangle {
	id: root
	implicitWidth: Math.max(header.implicitWidth + 40, weatherBox.implicitWidth + 40);
	implicitHeight: header.implicitHeight + weatherBox.implicitHeight + 60;
	
	Image {
		id: background
		source: "images/background.jpg"
		anchors.fill: parent
	}
	
	WeatherHeader {
		id: header
		anchors.top: root.top
		anchors.horizontalCenter: root.horizontalCenter
		anchors.topMargin: 20
		
		name: WeatherApp.currentLocation.name;
		location: WeatherApp.currentLocation.display;
		temp: WeatherApp.currentLocation.conditions.temp;
		weather: WeatherApp.currentLocation.conditions.weather;
		icon: WeatherApp.currentLocation.conditions.icon;
	}
	
	Rectangle {
		id: weatherBox
		//color: "#99333333" // temporary, for visualization - will be transparent
		color: "#00000000" // transparent
		radius: 4
		
		implicitWidth: conditions.implicitWidth;
		implicitHeight: conditions.implicitHeight;
		
		WeatherConditions {
			id: conditions
			anchors.centerIn: weatherBox
			windchill: WeatherApp.currentLocation.conditions.windchill;
			dewpoint: WeatherApp.currentLocation.conditions.dewpoint;
		}
		
		anchors {
			top: header.bottom; topMargin: 20;
			bottom: root.bottom; bottomMargin: 20;
			left: root.left; leftMargin: 20;
			right: root.right; rightMargin: 20;
		}
	}
	
	MouseArea {
		anchors.fill: parent
		onClicked: {
			Qt.quit();
		}
	}
}