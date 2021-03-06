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
		
	property bool is_valid: weatherLocation.valid
	
	implicitWidth: is_valid ? Math.max(400, icon.width + 80 + 2 * Math.max(
			Math.max(location.width, name.width), 
			Math.max(temp.width, weather.width))) : Math.max(400, noneView.width)
	implicitHeight: 6 + Math.max(Math.max(icon.height, name.height + location.height), temp.height + weather.height)
	
	property variant weatherLocation
	
	color: appStyle.panelColor;
	border.color: appStyle.borderColor;
	radius: appStyle.panelRadius;
	
//  	BorderImage {
//  		id: background
//  		source: "images/weather-header.png"
//  		anchors.fill: parent
//  	}
	
	Text {
		id: noneView
		anchors.centerIn: root
		opacity: !is_valid ? 1 : 0
		text: (weatherLocation.name == "") ? weatherLocation.location : (weatherLocation.name + " - " + weatherLocation.location)
		color: appStyle.textColor
		style: Text.Raised
		styleColor: appStyle.shadowColor
		font.pixelSize: appStyle.mainTitleFontSize
	}
	
	Item {
		id: regularView
		anchors.fill: root
		opacity: is_valid ? 1 : 0
	
		PlasmaCore.IconItem {
			id: icon
			anchors.centerIn: regularView
			
			source: weatherLocation.conditions.icon
			width: 64; height: 64;
		}
		
		Text {
			id: name
			color: appStyle.textColor
			style: Text.Raised
			styleColor: appStyle.shadowColor
			font.pixelSize: 20
			opacity: weatherLocation.name == "" ? 0 : 1
			anchors {
				bottom: regularView.verticalCenter
				right: icon.left
				rightMargin: 10
			}
			
			text: weatherLocation.name
		}
		
		Text {
			id: location
			color: appStyle.textColor
			style: Text.Raised
			styleColor: appStyle.shadowColor
			font.pixelSize: 16
			opacity: weatherLocation.name == "" ? 0 : 1
			anchors {
				top: regularView.verticalCenter
				right: icon.left
				rightMargin: 10
			}
			
			text: weatherLocation.location
		}
		
		Text {
			id: locationOnly
			color: appStyle.textColor
			style: Text.Raised
			styleColor: appStyle.shadowColor
			text: weatherLocation.location
			font.pixelSize: 18
			opacity: (weatherLocation.name == "") ? 1 : 0
			anchors {
				verticalCenter: regularView.verticalCenter
				right: icon.left
				rightMargin: 10
			}
		}
		
		Text {
			id: temp
			color: appStyle.textColor
			style: Text.Raised
			styleColor: appStyle.shadowColor
			font.pixelSize: 20
			anchors {
				bottom: regularView.verticalCenter
				left: icon.right
				leftMargin: 10
			}
			
			text: weatherLocation.conditions.temperature
		}
		
		Text {
			id: weather
			font.pixelSize: 16
			color: appStyle.textColor
			style: Text.Raised
			styleColor: appStyle.shadowColor
			anchors {
				top: regularView.verticalCenter
				left: icon.right
				leftMargin: 10
			}
			
			text: weatherLocation.conditions.summary
		}
	}
}
