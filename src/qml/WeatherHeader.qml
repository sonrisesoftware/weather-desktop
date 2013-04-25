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

Rectangle {
	id: root
	//width: 400
	//height: 64
	color: "#99333333"
	radius: 4
	
	implicitWidth: 400
	implicitHeight: 6 + Math.max(Math.max(icon.height, name.height + location.height), temp.height + weather.height)
	
	property alias name: name.text;
	property alias location: location.text;
	property alias icon: icon.source;
	property alias temp: temp.text;
	property alias weather: weather.text;
	
//  	BorderImage {
//  		id: background
//  		source: "images/weather-header.png"
//  		anchors.fill: parent
//  	}
	
	PlasmaCore.IconItem {
		id: icon
		width: 64; height: 64;
		anchors.centerIn: root
	}
	
	Text {
		id: name
		color: "white"
		font.pixelSize: 20
		anchors {
			bottom: root.verticalCenter
			right: icon.left
			rightMargin: 10
		}
	}
	
	Text {
		id: location
		color: "white"
		font.pixelSize: 16
		anchors {
			top: root.verticalCenter
			right: icon.left
			rightMargin: 10
		}
	}
	
	Text {
		id: temp
		color: "white"
		font.pixelSize: 20
		anchors {
			bottom: root.verticalCenter
			left: icon.right
			leftMargin: 10
		}
	}
	
	Text {
		id: weather
		font.pixelSize: 16
		color: "white"
		anchors {
			top: root.verticalCenter
			left: icon.right
			leftMargin: 10
		}
	}
}