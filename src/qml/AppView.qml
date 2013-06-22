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
// 	implicitWidth: Math.max(500, Math.max(header.implicitWidth + 40, weatherView.implicitWidth + 40));
// 	implicitHeight: topToolBar.height + Math.max(creditsText.height, infoText.height) + 5
// 			+ header.height + weatherView.implicitHeight + weatherAlerts.height + bottomToolBar.height + 80;

	implicitHeight: 400
	implicitWidth: 600
	
	property bool dropDownOpen: false
	
	anchors.fill: parent
	
	Image {
		id: backgroundImage
		source: WeatherApp.currentLocation.conditions.image || "../images/weather-clear.jpg"
		asynchronous: true
		anchors.fill: parent
		visible: root.opacity > 0
		
		onVisibleChanged: {
			if (visible) {
				source = background
			}
		}
	}
	
	PlasmaComponents.ToolBar {
		id: topToolBar
		
		tools: Row {
			spacing: 5
			
			Item {
				id: dropDownHeader
				anchors.verticalCenter: parent.verticalCenter
				width: childrenRect.width
				height: childrenRect.height
				
				Row {
					id: dropDownHeaderRow
					spacing: 5
					
					PlasmaCore.IconItem {
						id: dropDownIcon
						anchors.verticalCenter: parent.verticalCenter
						
						width: 16; height: 16;
						source: "arrow-right";
						rotation: dropDownOpen ? 90 : 0
						
						Behavior on rotation {
							NumberAnimation { duration: 250 }
						}	
					}
					
					Text {
						id: locationTitle
						anchors.verticalCenter: parent.verticalCenter
						
						text: WeatherApp.currentLocation.name + " (" + WeatherApp.currentLocation.location + ")"
						
						//style: Text.Raised
						//styleColor: "white"
						
						font.pixelSize: 16
						//font.bold: true
					}
				}
				
				MouseArea {
					id: mouseArea
					hoverEnabled: true
					anchors.fill: parent
					
					onClicked: {
						dropDownOpen = !dropDownOpen
					}
				}
			}
			
			Item {
				height: parent.height
				width: parent.width
						- dropDownHeader.width - configureButton.width
						- (parent.children.length - 1) * parent.spacing
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
	
	Row {
		id: infoText
		
		anchors {
			top: topToolBar.bottom
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
			visible: WeatherApp.currentLocation.error
			
			MouseArea {
				anchors.fill:parent
				onClicked: {
					showError(WeatherApp.currentLocation.location, WeatherApp.currentLocation.errorString)
				}
			}
		}
		
		Text {
			id: lastUpdatedText
			anchors.verticalCenter: parent.verticalCenter
			
			text: i18nc("The time the weather was last downloaded", 
						"Last updated at %1", Qt.formatTime(WeatherApp.currentLocation.lastUpdated))
						visible: WeatherApp.currentLocation.valid
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
	
	PlasmaComponents.ToolBar {
		id: bottomToolBar
		
		anchors {
			bottom: parent.bottom
		}
		
		tools: Row {
			spacing: 5
			
			PlasmaComponents.ToolButton {
				id: todayButton
				iconSource: "go-jump-today"
				text: i18n("Today")
				width: minimumWidth + 5
				onClicked: {
					weatherView.view = "today"
				}
				checked: weatherView.view == "today"
			}
			
			PlasmaComponents.ToolButton {
				id: hourlyButton
				
				iconSource: "clock"
				text: i18n("Hourly")
				width: minimumWidth + 5
				onClicked: {
					weatherView.view = "hourly"
				}
				checked: weatherView.view == "hourly"
			}
			
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
				width: parent.width
					- todayButton.width - dailyButton.width
					- hourlyButton.width - infoButton.width
					- (parent.children.length - 1) * parent.spacing
			}
			
			PlasmaComponents.ToolButton {
				id: infoButton
				iconSource: "help-about"
				onClicked: {
					//var position = mapToItem(null, 0, height)
					//WeatherApp.showMenu(position.x, position.y)
				}
			}
		}
	}
	
	property color viewColor: "black"
	
	WeatherView {
		id: weatherView
		weatherLocation: WeatherApp.currentLocation
		anchors {
			top: topToolBar.bottom
			left: parent.left
			right: parent.right
			bottom: bottomToolBar.top
			margins: 10
		}
	}
}
