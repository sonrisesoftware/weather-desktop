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
	implicitWidth: Math.max(header.implicitWidth + 40, weatherView.implicitWidth + 40) + listPanel.width;
	implicitHeight: topToolBar.height + header.height + weatherView.implicitHeight + 60;
	
	property variant appStyle: Style {
		id: style
	}
	
	Item {
		id: content
		anchors {
			left: listPanel.right;
			top: parent.top;
			bottom: parent.bottom;
			right: parent.right;
		}
		
		Image {
			id: background
			//source: "images/background.jpg"
			source: "images/weather-clear.jpg"
			anchors.fill: parent
		}
		
		WeatherHeader {
			id: header
			anchors.top: parent.top
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.topMargin: 20
			
			name: WeatherApp.currentLocation.name;
			location: WeatherApp.currentLocation.display;
			temp: WeatherApp.currentLocation.conditions.temp;
			weather: WeatherApp.currentLocation.conditions.weather;
			icon: WeatherApp.currentLocation.conditions.icon;
		}
			
		WeatherView {
			id: weatherView
				
			anchors {
				top: header.bottom; topMargin: 20;
				bottom: parent.bottom; bottomMargin: 20;
				left: parent.left; leftMargin: 20;
				right: parent.right; rightMargin: 20;
			}
		}
		
		PlasmaComponents.ToolBar {
			id: topToolBar
			//width: parent.width
			
			tools: Row {
				anchors.leftMargin: 3
				anchors.rightMargin: 3
				spacing: 5

				PlasmaComponents.ToolButton {
					id: refreshButton
					iconSource: (WeatherApp.currentLocation.updating) ?"process-stop" : "view-refresh"
					text: (WeatherApp.currentLocation.updating) ? i18n("Stop") : i18n("Refresh")
					onClicked: (WeatherApp.currentLocation.updating) ? 
							WeatherApp.currentLocation.stopAllRefresh() : WeatherApp.currentLocation.refreshAll()
					width: minimumWidth + 5
					opacity: (WeatherApp.currentLocation.needsUpdate) ? 1 : 0
				}
				
				Text {
					id: lastUpdatedText
					text: i18nc("The time the weather was last downloaded", 
								"Last updated at %1", Qt.formatTime(WeatherApp.currentLocation.lastUpdated))
					opacity: (WeatherApp.currentLocation.needsUpdate) ? 0 : 1
				}
				
				PlasmaComponents.ToolButton {
					iconSource: "arrow-down-double"
					text: i18n("Now")
					width: minimumWidth + 5
					onClicked: {
						weatherView.view = "conditions"
					}
					checked: weatherView.view == "conditions"
				}
				
				PlasmaComponents.ToolButton {
					iconSource: "clock"
					text: i18n("Hourly")
					width: minimumWidth + 5
					onClicked: {
						weatherView.view = "hourly"
					}
					checked: weatherView.view == "hourly"
				}
				
				PlasmaComponents.ToolButton {
					iconSource: "view-calendar-day"
					text: i18n("Daily")
					width: minimumWidth + 5
					onClicked: {
						weatherView.view = "daily"
					}
					checked: weatherView.view == "daily"
				}
			}
		}
	}
	
	Component  {
		id: tileitem
		
		Item {
			width: 210
			height: 110
			
			WeatherTile {
				anchors.centerIn: parent;
				title: modelData.name;
				temp: modelData.conditions.temp;
				icon: modelData.conditions.icon;
				weather: modelData.conditions.weather;
			}
		}
	}
	
	Rectangle {
		id: listPanel
		color: "lightblue"
		//color: appStyle.panelColor;
		anchors {
			left: root.left;
			top: root.top;
			bottom: root.bottom;
		}
		
		width: 210
	
		PlasmaWidgets.LineEdit {
			id: searchBox;
			//anchors.verticalCenter: parent.verticalCenter
			anchors.top: parent.top
			
			width: parent.width
			//iconSource: "go-home"
			clickMessage: i18n("Search...")
			clearButtonShown: true
			onReturnPressed: WeatherApp.setLocation(text)
		}
		
		ListView {
			id: list
			clip: true
			anchors {
				left: parent.left;
				top: searchBox.bottom;
				right: parent.right;
				bottom: parent.bottom;
			}
			
			model: WeatherApp.locations;
			delegate: tileitem;
			
			highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
			focus: true
		}
	}
}
