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

Item {
	id: root
	property variant weather: weatherLocation.dailyForecast.at(0);
	property variant weatherLocation
	property variant conditions: weatherLocation.conditions;
	
	PlasmaCore.IconItem {
		id: icon
		anchors.centerIn: parent
		
		width: 128; height: width;
		source: weather.icon;
	}
	
	Column {
		spacing: 5
		
		anchors {
			left: parent.left
			bottom: parent.bottom
		}
		
		Text {
			color: viewColor
			text: "Today"
		}
		
		Row {
			spacing: 5
			
			Text {
				id: weatherTemp
				anchors.verticalCenter: parent.verticalCenter
				text: conditions.temperature
				font.pixelSize: 60
				color: viewColor
			}
			
			Column {
				anchors.verticalCenter: parent.verticalCenter	
				spacing: 5
				
				Text {
					text: weather.temperatureMax
					font.pixelSize: 27
					color: "#c31f1f"
				}
				
				Text {
					text: weather.temperatureMin
					font.pixelSize: 27
					color: "#217ecd"
				}
			}
			
			Column {
				spacing: 5
				anchors.verticalCenter: parent.verticalCenter
				
				Text {
					id: weatherSummary
					
					text: weather.summary
					font.pixelSize: 20
					color: viewColor
				}
				
				Grid {
					columns: 3
					spacing: 5
					
					Text {
						text: "Precipitation: " + conditions.precip
						width: implicitWidth + 10
						color: viewColor
					}
					
					Text {
						text: i18n("Cloud Cover: %1", conditions.cloudCover)
						width: implicitWidth + 10
						color: viewColor
					}
					
					Text {
						text: "Wind: " + conditions.wind
						width: implicitWidth + 10
						color: viewColor
					}
					
					Text {
						text: "Pressure: " + conditions.pressure
						width: implicitWidth + 10
						color: viewColor
					}
					
					Text {
						text: "Humidity: " + conditions.humidity
						width: implicitWidth + 10
						color: viewColor
					}
					
					Text {
						text: i18n("Visibility: %1", conditions.visibility)
						width: implicitWidth + 10
						color: viewColor
					}
				}
			}
		}
	}
}
