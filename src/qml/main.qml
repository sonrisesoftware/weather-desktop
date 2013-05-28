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
	implicitWidth: Math.max(header.implicitWidth + 40, weatherView.implicitWidth + 40);
	//implicitHeight: topToolBar.height + header.height + weatherView.implicitHeight + 60;
	implicitHeight: topToolBar.height + Math.max(creditsText.height, lastUpdatedText.height) + 5
			+ header.height + weatherView.implicitHeight + bottomToolBar.height + 60;
	
	property variant appStyle: Style {
		id: style
	}
	
	Image {
		id: background
		source: "images/weather-clear.jpg"
		anchors.fill: parent
	}
	
	/*Rectangle {
		width: 1
		anchors {
			top: parent.top
			left: listPanel.right
			bottom: parent.bottom
		}
		
		color: appStyle.borderColor
	}*/
	
	Item {
		id: content
		anchors {
			left: parent.left;
			top: parent.top;
			bottom: parent.bottom;
			right: parent.right;
		}
		
		WeatherHeader {
			id: header
			anchors.top: lastUpdatedText.bottom
			//anchors.top: parent.top
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.topMargin: 20
			name: WeatherApp.currentLocation.name;
			location: WeatherApp.currentLocation.display;
			temp: WeatherApp.currentLocation.conditions.temperature;
			weather: WeatherApp.currentLocation.conditions.summary;
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
		
		PlasmaComponents.ToolBar {
			id: topToolBar
			
			tools: Row {
				//anchors.leftMargin: 3
				//anchors.rightMargin: 3
				spacing: 5
				
				PlasmaComponents.ToolButton {
					id: refreshButton
					//iconSource: (WeatherApp.currentLocation.refreshing) ?"process-stop" : "view-refresh"
					iconSource: "view-refresh"
					//text: (WeatherApp.currentLocation.refreshing) ? i18n("Stop") : i18n("Refresh")
					text: i18n("Refresh")
					onClicked: WeatherApp.currentLocation.refresh()
					//onClicked: (WeatherApp.currentLocation.refreshing) ? 
					//		WeatherApp.currentLocation.cancelRefresh() : WeatherApp.currentLocation.refresh()
					width: minimumWidth + 5
					//visible: WeatherApp.currentLocation.needsRefresh || WeatherApp.currentLocation.refreshing
				}
				
				PlasmaWidgets.Separator {
					id: refreshSeparator
					height: parent.height
					orientation: Qt.Vertical
				}

				PlasmaComponents.ToolButton {
					id: nowButton
					iconSource: "arrow-down-double"
					text: i18n("Now")
					width: minimumWidth + 5
					onClicked: {
						weatherView.view = "conditions"
					}
					checked: weatherView.view == "conditions"
				}
				
				/*PlasmaComponents.ToolButton {
					iconSource: "clock"
					text: i18n("Hourly")
					width: minimumWidth + 5
					onClicked: {
						weatherView.view = "hourly"
					}
					checked: weatherView.view == "hourly"
				}*/
				
				PlasmaComponents.ToolButton {
					id: dailyButton
					iconSource: "view-calendar-day"
					text: i18n("Daily")
					width: minimumWidth + 5
					onClicked: {
						weatherView.view = "daily"
					}
					checked: weatherView.view == "daily"
				}
				
				Item {
					height: parent.height
					width: parent.width - refreshButton.width
							- refreshSeparator.width
							- nowButton.width - dailyButton.width
							- searchField.width - configureButton.width
							- (parent.children.length - 1) * parent.spacing
				}
				
				PlasmaWidgets.LineEdit {
					id: searchField;
					
					clickMessage: i18n("Search...")
					clearButtonShown: true
					onReturnPressed: WeatherApp.setLocation(text)
				}
				
				PlasmaComponents.ToolButton {
					id: configureButton
					iconSource: "configure"
					onClicked: {
						var position = mapToItem(null, 0, height)
						WeatherApp.showMenu(position.x, position.y)
					}
				}
			}
		}
		
		Text {
			id: lastUpdatedText
			
			anchors {
				top: topToolBar.bottom
				margins: 5
				left: parent.left
			}
			
			text: i18nc("The time the weather was last downloaded", 
						"Last updated at %1", Qt.formatTime(WeatherApp.currentLocation.lastUpdated))
		}
		
		Text {
			id: creditsText
			
			anchors {
				top: topToolBar.bottom
				margins: 5
				right: parent.right
			}
			
			text: i18nc("Credits for the weather data", "Powered by <a href=\"http://forecast.io/\">Forecast.io</a>")
			textFormat: Text.RichText;
			onLinkActivated: {
				Qt.openUrlExternally(link)
			}
		}
		
		PlasmaComponents.ToolBar {
			id: bottomToolBar
			//width: parent.width
			
			anchors.bottom: parent.bottom
			
			tools: Row {
				anchors.leftMargin: 3
				anchors.rightMargin: 3
				spacing: 5
				
				ListView {
					id: list
					
					height: 100
					width: parent.width
							- listActions.width - actionsSeparator.width
							- (parent.children.length - 1) * parent.spacing
					
					orientation: ListView.Horizontal
					
					spacing: 5
					model: WeatherApp.locations;
					delegate: tileitem;
					
					focus: true
				}
				
				PlasmaWidgets.Separator {
					id: actionsSeparator
					height: parent.height
					orientation: Qt.Vertical
				}
				
				Column {
					id: listActions
					anchors.verticalCenter: parent.verticalCenter
					
					spacing: 20
					
					PlasmaComponents.ToolButton {
						iconSource: "list-add"
						//text: i18n("Add")
						onClicked: WeatherApp.addCurrentLocation()
						//width: minimumWidth + 5
					}
					
					PlasmaComponents.ToolButton {
						iconSource: "edit-delete"
						//text: i18n("Delete")
						onClicked: WeatherApp.removeCurrentLocation()
						//width: minimumWidth + 5
					}
				}
			}
		}
	}
	
	Component  {
		id: tileitem
		
		Item {
			id: wrapper
			
			width: 200
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
				temp: modelData.conditions.temperature;
				icon: modelData.conditions.icon;
				weather: modelData.conditions.summary;
				
				//tempForecast: modelData.dailyForecast.at(0).temperatureMax;
				iconForecast: modelData.dailyForecast.length > 0 ? modelData.dailyForecast.at(0).icon : "weather-desktop";
				weatherForecast: modelData.dailyForecast.length > 0 ? modelData.dailyForecast.at(0).summary : "No forecast available";
			}
		}
	}
}
