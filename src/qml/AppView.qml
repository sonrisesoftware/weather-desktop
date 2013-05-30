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
	implicitWidth: Math.max(locations.currentItem.header.implicitWidth + 40, locations.currentItem.view.implicitWidth + 40);
	implicitHeight: topToolBar.height + locations.currentItem.minimumHeight + bottomToolBar.height;
	
	anchors {
		left: parent.left;
		top: parent.top;
		bottom: parent.bottom;
		right: parent.right;
	}
	
	property string view: "today"
	
	property variant currentLocation: WeatherApp.currentLocation
	
	onCurrentLocationChanged: {
		var index = WeatherApp.locations.indexOf(currentLocation)
		if (index != -1) {
			locations.currentIndex = index
		}
	}
	
	ListView {
		id: locations
		anchors.fill: parent
		
		clip: true
		highlightMoveSpeed: 2500
		
		orientation: ListView.Horizontal
		model: WeatherApp.locations;
		
		snapMode: ListView.SnapOneItem
		
		delegate: Item {
			id: locationView
			width: locations.width
			height: locations.height
			
			property real minimumHeight: infoText.height + weatherView.implicitHeight + weatherHeader.height + 65
			
			property url background: modelData.conditions.image || "../images/weather-clear.jpg"
			property variant weatherLocation: modelData
			property variant header: weatherHeader
			property variant view: weatherView
			
			onBackgroundChanged: {
				if (backgroundImage.visible) {
					backgroundImage.source = background
				}
			}
			
			Image {
				id: backgroundImage
				source: "../images/weather-clear.jpg"
				anchors.fill: parent
				visible: root.opacity > 0
				
				onVisibleChanged: {
					if (visible) {
						source = background
					}
				}
			}
			
// 			Rectangle {
// 				id: nightTimeShading
// 				anchors.fill: parent
// 				opacity: WeatherApp.currentLocation.day ? 0 : 1
// 				color: Qt.rgba(0,0,0,0.7)
// 				 
// 				Behavior on opacity {
// 					 NumberAnimation { duration: 500 }
// 				}
// 			}
			
			WeatherHeader {
				id: weatherHeader
				
				anchors {
					top: infoText.bottom; 
					horizontalCenter: parent.horizontalCenter;
					margins: 20;
				}
				
				weatherLocation: modelData
			}
			
			WeatherView {
				id: weatherView
				
				height: Math.max(implicitHeight, root.height - (weatherHeader.y + weatherHeader.height + 20) - (bottomToolBar.height + 20))
				
				anchors {
					top: weatherHeader.bottom; margins: 20;
					//bottom: bottomToolBar.top;
					left: parent.left;
					right: parent.right;
				}
				
				view: root.view
				
				weatherLocation: modelData
			}
			
			Row {
				id: infoText
				
				y: topToolBar.height + 5
				
				anchors {
					margins: 5
					left: parent.left
					right: parent.right
				}
				
				PlasmaCore.IconItem {
					id: statusIcon
					anchors.verticalCenter: parent.verticalCenter
					
					width: visible ? height : 0;
					height: 16;
					source: "dialog-warning"
					visible: weatherLocation.error
					
					MouseArea {
						anchors.fill:parent
						onClicked: {
							showError(weatherLocation.location, weatherLocation.errorString)
						}
					}
				}
				
				Text {
					id: lastUpdatedText
					anchors.verticalCenter: parent.verticalCenter
					
					text: i18nc("The time the weather was last downloaded", 
					"Last updated at %1", Qt.formatTime(weatherLocation.lastUpdated))
					visible: weatherLocation.valid
					width: visible ? implicitWidth : 0;
				}
				
				Item {
					height: parent.height
					width: parent.width - creditsText.width
					- lastUpdatedText.width - statusIcon.width
					- (parent.children.length - 1) * parent.spacing
				}
				
				Text {
					id: creditsText
					anchors.verticalCenter: parent.verticalCenter
					
					text: i18nc("Credits for the weather data", "Powered by <a href=\"http://forecast.io/\">Forecast.io</a>")
					textFormat: Text.RichText;
					onLinkActivated: {
						Qt.openUrlExternally(link)
					}
				}
			}
		}
	}
	
	PlasmaComponents.ToolBar {
		id: topToolBar
		
		tools: Row {
			//anchors.leftMargin: 3
			//anchors.rightMargin: 3
			spacing: 5
			
			Row {
				id: refreshTools
				spacing: 5
				
				PlasmaComponents.ToolButton {
					id: refreshButton
					iconSource: "view-refresh"
					text: i18n("Refresh")
					onClicked: WeatherApp.currentLocation.refresh()
					width: minimumWidth + 5
					visible: WeatherApp.currentLocation != null && 
							WeatherApp.currentLocation.needsRefresh &&
							!WeatherApp.currentLocation.refreshing
				}
				
				PlasmaWidgets.BusyWidget {
					id: refreshingWidget
					anchors.verticalCenter: parent.verticalCenter
					
					width: height
					height: refreshButton.height
					visible: WeatherApp.currentLocation != null && 
							WeatherApp.currentLocation.refreshing
					running: true
				}
				
				Text {
					id: refreshingLabel
					anchors.verticalCenter: parent.verticalCenter
					
					text: "Refreshing"
					visible: refreshingWidget.visible
				}
				
				PlasmaWidgets.Separator {
					id: refreshSeparator
					height: parent.height
					orientation: Qt.Vertical
					visible: refreshingWidget.visible || refreshButton.visible
				}
			}
			
			/*PlasmaComponents.ToolButton {
				id: nowButton
				iconSource: "arrow-down-double"
				text: i18n("Now")
				width: minimumWidth + 5
				onClicked: {
					weatherView.view = "conditions"
				}
				checked: weatherView.view == "conditions"
			}*/
			
			PlasmaComponents.ToolButton {
				id: todayButton
				iconSource: "go-jump-today"
				text: i18n("Today")
				width: minimumWidth + 5
				onClicked: {
					root.view = "today"
				}
				checked: root.view == "today"
			}
			
			/*PlasmaComponents.ToolButton {
			 *		iconSource: "clock"
			 *		text: i18n("Hourly")
			 *		width: minimumWidth + 5
			 *		onClicked: {
			 *			weatherView.view = "hourly"
			 }
			 checked: weatherView.view == "hourly"
			 }*/
			
			PlasmaComponents.ToolButton {
				id: dailyButton
				iconSource: "view-calendar-day"
				text: i18n("Daily")
				width: minimumWidth + 5
				onClicked: {
					root.view = "daily"
				}
				checked: root.view == "daily"
			}
			
			Item {
				height: parent.height
				width: parent.width - refreshTools.width
						- todayButton.width - dailyButton.width
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
				clip: true
				
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
	
	Component  {
		id: tileitem
		
		Item {
			id: wrapper
			
			width: 200
			height: 100
			
			WeatherTile {
				anchors.centerIn: parent;
				selected: WeatherApp.currentLocation != null && modelData.location == WeatherApp.currentLocation.location;
				
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
