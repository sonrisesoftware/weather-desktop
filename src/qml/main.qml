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
	/*implicitWidth: Math.max(Math.max(Math.max(header.implicitWidth + 40, weatherView.implicitWidth + 40),
									 2 * Math.max(refreshToolBar.width, settingsToolBar.width) + viewToolBar.width +  30),
						    locationsToolBar.width + searchBar.width + 20);
	implicitHeight: viewToolBar.height + header.height + weatherView.implicitHeight + locationsToolBar.height + 60;*/
	
	implicitWidth: Math.max(Math.max(Math.max(header.implicitWidth + 40, weatherView.implicitWidth + 40),
							refreshToolBar.width + 20), locationsToolBar.width + searchBar.width + 20);
	implicitHeight: refreshToolBar.height + header.height + weatherView.implicitHeight + locationsToolBar.height + 60;
	
	property variant appStyle: Style {
		id: style
	}
	
	Image {
		id: background
		//source: "images/background.jpg"
		source: "/home/mspencer/Pictures/weather-cloudy-001.jpg"
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
		
	WeatherView {
		id: weatherView
			
		anchors {
			top: header.bottom; topMargin: 20;
			bottom: locationsToolBar.top; bottomMargin: 20;
			left: root.left; leftMargin: 20;
			right: root.right; rightMargin: 20;
		}
	}
	
	PlasmaComponents.ToolBar {
		id: refreshToolBar
		// Hack to resize toolbar when button changes or switches to text
		width: (WeatherApp.currentLocation.needsUpdate ? refreshButton.width : lastUpdatedText.width) + 15
		opacity: (root.width > (header.width + 40 + 2 * refreshToolBar.width)) ? 1 :0
		
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
		
				/*Behavior on opacity {
					NumberAnimation { duration: 500 }
				}*/
			}
			
			Text {
				id: lastUpdatedText
				text: i18n("Last updated at %1", Qt.formatTime(WeatherApp.currentLocation.lastUpdated))
				opacity: (WeatherApp.currentLocation.needsUpdate) ? 0 : 1
		
				/*Behavior on opacity {
					NumberAnimation { duration: 500 }
				}*/
			}
		}
	}
	/*
	PlasmaComponents.ToolBar {
		id: viewToolBar
		width: tools.width + 15
	
		anchors.horizontalCenter: root.horizontalCenter
	
		tools: Row {
			anchors.leftMargin: 3
			anchors.rightMargin: 3
			spacing: 5

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
	
	PlasmaComponents.ToolBar {
		id: settingsToolBar
		width: tools.width + 15
	
		anchors.right: root.right
	
		tools: Row {
			anchors.leftMargin: 3
			anchors.rightMargin: 3
			spacing: 5

			PlasmaComponents.ToolButton {
				iconSource: "configure"
				text: i18n("Configure")
				width: minimumWidth + 5
			}
		}
	}*/
	
	PlasmaComponents.ToolBar {
		id: locationsToolBar
		width: tools.width + 15
	
		anchors.bottom: root.bottom
	
		tools: Row {
			id: toolsRow;
			anchors.leftMargin: 3
			anchors.rightMargin: 3
			spacing: 5
			
			PlasmaComponents.ToolButton {
				iconSource: "list-add"
				//text: i18n("Home")
				onClicked: WeatherApp.addCurrentLocation()
				width: minimumWidth + 5
			}
			
			PlasmaComponents.ToolButton {
				iconSource: "list-remove"
				//text: i18n("Home")
				onClicked: WeatherApp.removeCurrentLocation()
				width: minimumWidth + 5
			}
			
			Repeater {
				model: WeatherApp.locationNames.length
				
				delegate: PlasmaComponents.ToolButton {
					iconSource: WeatherApp.location(modelData).conditions.icon;
					text: WeatherApp.location(modelData).name;
					onClicked: {
						WeatherApp.setCurrentLocation(WeatherApp.location(modelData))
					}
					checked: WeatherApp.currentLocation == WeatherApp.location(modelData)
					width: minimumWidth + 5
				}
			}
		}
	}
	
	PlasmaComponents.ToolBar {
		id: searchBar
		width: tools.width + 15
	
		anchors.bottom: root.bottom
		anchors.right: root.right
	
		tools: Row {
			anchors.leftMargin: 3
			anchors.rightMargin: 3
			spacing: 5

			PlasmaWidgets.LineEdit {
				//iconSource: "go-home"
				clickMessage: i18n("Search...")
				clearButtonShown: true
				onReturnPressed: WeatherApp.setLocation(text)
				width: minimumWidth + 5
			}
		}
	}
}
