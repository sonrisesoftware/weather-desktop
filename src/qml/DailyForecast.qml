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

Panel {
	id: root
	
	// FIXME: Why doesn't the WeatherPanel version work???
	implicitWidth: Math.max(header.width + 10, days.width + 10)
	implicitHeight: header.height + 200 + 30

	title: "Daily Forecast"
	
	Component {
		id: dayForecast
		
		Rectangle {
			id: dayItem
			
			property variant modelData: WeatherApp.currentLocation.dailyForecast.at(index)
			color: Qt.rgba(33/256,126/256,205/256,0.5)
			width: 64 + 60
			height: 160
			
			Text {
				id: title
				//width: parent.width - 10
				
				text: today ? "Today" : Qt.formatDate(modelData.time, "dddd")
				property bool today: Qt.formatDate(modelData.time) == Qt.formatDate(new Date())
				onTextChanged: {
					console.log(Qt.formatDate(modelData.time) + " == " + Qt.formatDate(new Date()))
				}
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				//wrapMode: Text.Wrap
				
				anchors {
					topMargin: 10
					top: parent.top
					horizontalCenter: parent.horizontalCenter
				}
			}
			
			PlasmaCore.IconItem {
				id: icon
				width: 64; height: 64;
				source: modelData.icon
				
				anchors {
					topMargin: 10
					top: title.bottom
					horizontalCenter: parent.horizontalCenter
				}
			}
			
			Text {
				id: probability
				//width: parent.width - 10
				
				text: modelData.precipProbability
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				anchors {
					topMargin: 20
					top: icon.bottom
					horizontalCenter: parent.horizontalCenter
				}
			}
			
			Text {
				id: summary
				//width: parent.width - 10
				
				text: modelData.precip
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				//wrapMode: Text.Wrap
				
				anchors {
					bottomMargin: 10
					bottom: parent.bottom
					horizontalCenter: parent.horizontalCenter
				}
			}
		}
	}
	
	Row {
		id: days
		anchors {
			top: header.bottom
			topMargin: 15
			horizontalCenter: parent.horizontalCenter
		}
		
		spacing: 5
	
		Repeater {
			model: Math.min(WeatherApp.currentLocation.dailyForecast.length, 4)
			delegate: dayForecast
		}
	
	}
}