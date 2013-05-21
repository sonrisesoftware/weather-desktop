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
	//implicitHeight: topToolBar.height + header.height + weatherView.implicitHeight + 60;
	implicitHeight: header.height + weatherView.implicitHeight + bottomToolBar.height + 60;
	
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
			source: "images/weather-clear.jpg"
			anchors.fill: parent
		}
		
		WeatherHeader {
			id: header
			//anchors.top: topToolBar.bottom
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
				bottom: bottomToolBar.top; bottomMargin: 20;
				left: parent.left; leftMargin: 20;
				right: parent.right; rightMargin: 20;
			}
		}
		
		/*PlasmaComponents.ToolBar {
			id: topToolBar
			//width: parent.width
			
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
		}*/
		
		PlasmaComponents.ToolBar {
			id: bottomToolBar
			width: tools.implicitWidth + 10
			anchors.bottom: parent.bottom
			
			tools: Row {
				anchors.leftMargin: 3
				anchors.rightMargin: 3
				spacing: 5

				PlasmaComponents.ToolButton {
					id: refreshButton
					iconSource: (WeatherApp.currentLocation.refreshing) ?"process-stop" : "view-refresh"
					text: (WeatherApp.currentLocation.refreshing) ? i18n("Stop") : i18n("Refresh")
					onClicked: (WeatherApp.currentLocation.refreshing) ? 
							WeatherApp.currentLocation.stopRefresh() : WeatherApp.currentLocation.refresh()
					width: minimumWidth + 5
					opacity: (WeatherApp.currentLocation.needsRefresh) ? 1 : 0
				}
				
				Text {
					id: lastUpdatedText
					text: i18nc("The time the weather was last downloaded", 
								"Last updated at %1", Qt.formatTime(WeatherApp.currentLocation.lastUpdated))
					opacity: (WeatherApp.currentLocation.needsRefresh) ? 0 : 1
				}
			}
		}
	}
	
	Component  {
		id: tileitem
		
		Item {
			id: wrapper
			
			width: 210
			height: 100
			
			WeatherTile {
				anchors.centerIn: parent;
				selected: modelData.location == WeatherApp.currentLocation.location;
				
				onSelectedChanged: {
					if (selected) {
						wrapper.ListView.view.currentIndex = index
					} else {
						wrapper.ListView.view.currentIndex = -1
					}
				}
				
				onClicked: {
					WeatherApp.currentLocation = modelData
				}
				
				title: modelData.name;
				temp: modelData.conditions.temp;
				icon: modelData.conditions.icon;
				weather: modelData.conditions.weather;
			}
		}
	}
	
	Rectangle {
		id: listPanel
		color: "#3e3d39"
		anchors {
			left: root.left;
			top: root.top;
			bottom: root.bottom;
		}
		
		width: 210
	
		PlasmaWidgets.LineEdit {
			id: searchBox;
			anchors {
				top: parent.top;
				topMargin: 5;
				left: parent.left
				leftMargin: 5;
				right: parent.right;
				rightMargin: 5;
			}
			clickMessage: i18n("Search...")
			clearButtonShown: true
			onReturnPressed: WeatherApp.setLocation(text)
		}
		
		List {
			id: list
			
			anchors {
				left: parent.left;
				top: searchBox.bottom;
				topMargin: 5;
				right: parent.right;
				bottom: listActions.top;
				bottomMargin: 5;
			}
			
			spacing: 5
			model: WeatherApp.locations;
			delegate: tileitem;
			
			focus: true
		}
		
		Row {
			id: listActions
			anchors {
				//left: parent.left;
				//leftMargin: 5;
				//right: parent.right;
				//rightMargin: 5;
				bottom: parent.bottom;
				bottomMargin: 5;
				horizontalCenter: parent.horizontalCenter
			}
			
			spacing: 5
			
			PlasmaComponents.ToolButton {
				iconSource: "list-add"
				text: i18n("Add")
				onClicked: WeatherApp.addCurrentLocation()
				width: minimumWidth + 5
			}
			
			PlasmaComponents.ToolButton {
				iconSource: "list-remove"
				text: i18n("Delete")
				onClicked: WeatherApp.removeCurrentLocation()
				width: minimumWidth + 5
			}
		}
	}
}
