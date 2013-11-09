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
    implicitWidth: Math.max(680, Math.max(header.implicitWidth + 40, weatherView.implicitWidth + 40))
    implicitHeight: Math.max(505, topToolBar.height
            + header.height + weatherView.implicitHeight + weatherAlerts.height + bottomToolBar.height + 60);
	
    property url background: WeatherApp.currentLocation.conditions.image || "../images/weather-clear.jpg"
	
    onBackgroundChanged: {
        if (backgroundImage.visible) {
            backgroundImage.source = background
        }
    }

    anchors {
        left: parent.left;
        top: parent.top;
        bottom: parent.bottom;
        right: parent.right;
    }
	
    Image {
        id: backgroundImage
        source: "../images/weather-clear.jpg"
        anchors.fill: parent
        visible: root.opacity > 0


        fillMode: Image.PreserveAspectCrop
		
        onVisibleChanged: {
            if (visible) {
                source = background
            }
        }
    }
	
//// 	Rectangle {
//// 		id: nightTimeShading
//// 		anchors.fill: parent
//// 		opacity: WeatherApp.currentLocation.day ? 0 : 1
//// 		color: Qt.rgba(0,0,0,0.6)
////
//// 		Behavior on opacity {
//// 			NumberAnimation { duration: 500 }
//// 		}
//// 	}
	
////    WeatherHeader {
////        id: header
////        anchors.top: topToolBar.bottom
////        //anchors.top: parent.top
////        anchors.horizontalCenter: parent.horizontalCenter
////        anchors.topMargin: 20
////        weatherLocation: WeatherApp.currentLocation
////    }

    Text {
        id: header
        anchors {
            top: topToolBar.bottom
            margins: 10
            left: parent.left
        }

        smooth: true

        text: WeatherApp.currentLocation.location//weatherView.title
        font.pixelSize: 24
        color: "white"

        style: Text.Raised
        styleColor: appStyle.shadowColor
    }

    Text {
        id: timeHeader

        anchors {
            top: topToolBar.bottom
            margins: 10
            right: parent.right
        }

        font.pixelSize: 24
        color: "white"

        style: Text.Raised
        styleColor: appStyle.shadowColor

        text: Qt.formatTime(currentTime)
        property date currentTime: new Date()

        Timer {
            running: true
            repeat: true
            interval: 10 * 1000 // 1 min
            onTriggered: {
                currentTime = new Date()
            }
        }
    }
	
    WeatherView {
        id: weatherView
		
        anchors {
            top: header.bottom
            bottom: weatherAlerts.top;
            margins: 20
            left: parent.left;
            right: parent.right
        }
		
        weatherLocation: WeatherApp.currentLocation
    }
	
    Column {
        id: weatherAlerts
		
        anchors {
            bottom: bottomToolBar.top; bottomMargin: 20;
            left: parent.left; leftMargin: 20;
            right: parent.right; rightMargin: 20;
        }
		
        spacing: 3
	
        Repeater {
			
            model: WeatherApp.currentLocation.alerts.length
			
            delegate: Alert {
                id: item
                alert: WeatherApp.currentLocation.alerts.at(index)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.min(Math.max(root.width - 40, item.implicitWidth), 800)
            }
        }
    }
	
    PlasmaComponents.ToolBar {
        id: topToolBar
		
        tools: Row {
            //anchors.leftMargin: 3
            //anchors.rightMargin: 3
            spacing: 5
			
            PlasmaComponents.ToolButton {
                id: locationButton
                text: WeatherApp.currentLocation.name !== ""
                      ? WeatherApp.currentLocation.name + " (" + WeatherApp.currentLocation.location + ")"
                      : WeatherApp.currentLocation.location
                width: minimumWidth+ 5
                onClicked: {
                    if (locationsSheet.show) {
                        locationsSheet.close()
                    } else {
                        locationsSheet.open()
                    }
                }
                checked: locationsSheet.show
            }
			
            Item {
                height: parent.height
                width: parent.width
                        - locationButton.width - configureButton.width
                        - (parent.children.length - 1) * parent.spacing
            }
			
            PlasmaComponents.ToolButton {
                id: configureButton
                iconSource: "configure"
                onClicked: {
                    //settingsSheet.open()

                    var position = mapToItem(null, 0, height)
                    WeatherApp.showMenu(position.x, position.y)
                }
            }
        }
    }
	
//    Row {
//		id: locationInfoText
		
//		anchors {
//			bottom: bottomToolBar.top
//			margins: 5
//			left: parent.left
//			right: parent.right
//		}
		
//		Text {
//			id: locationText
//			anchors.verticalCenter: parent.verticalCenter
			
//			text: WeatherApp.currentLocation.display
//		}
//	}

    PlasmaComponents.ToolBar {
        id: bottomToolBar
		
        anchors.bottom: parent.bottom
		
        tools: Row {
//			anchors.leftMargin: 3
//			anchors.rightMargin: 3
            spacing: 5

            PlasmaComponents.ToolButton {
                id: nowButton
                iconSource: "download"
                text: i18n("Now")
                width: minimumWidth+ 5
                onClicked: {
                    weatherView.view = "conditions"
                }
                checked: weatherView.view == "conditions"
            }

            PlasmaComponents.ToolButton {
                id: todayButton
                iconSource: "go-jump-today"
                text: i18n("Today")
                width: minimumWidth+ 5
                onClicked: {
                    weatherView.view = "today"
                }
                checked: weatherView.view == "today"
            }

            PlasmaComponents.ToolButton {
                id: hourlyButton

                iconSource: "clock"
                text: i18n("Hourly")
                width: minimumWidth+ 5
                onClicked: {
                    weatherView.view = "hourly"
                }
                checked: weatherView.view == "hourly"
            }

            PlasmaComponents.ToolButton {
                id: dailyButton
                iconSource: "view-calendar-day"
                text: i18n("Daily")
                width: minimumWidth+ 5
                onClicked: {
                    weatherView.view = "daily"
                }
                checked: weatherView.view == "daily"
            }

            Item {
                height: parent.height
                width: parent.width
                        - refreshTools.width - todayButton.width
                        - dailyButton.width - hourlyButton.width
                        - statusButton.width - infoButton.width
                        - nowButton.width + 5
                        - (parent.children.length - 1) * parent.spacing
            }

            Row {
                id: refreshTools
                spacing: 5

                PlasmaComponents.ToolButton {
                    id: refreshButton
                    iconSource: "view-refresh"
                    text: i18n("Refresh")
                    onClicked: WeatherApp.currentLocation.refresh()
                    width: minimumWidth + 5
                    visible: WeatherApp.currentLocation.needsRefresh && !WeatherApp.currentLocation.refreshing
                }

                PlasmaWidgets.BusyWidget {
                    id: refreshingWidget
                    anchors.verticalCenter: parent.verticalCenter

                    width: height
                    height: refreshButton.height
                    visible: WeatherApp.currentLocation.refreshing
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

            PlasmaComponents.ToolButton {
                id: statusButton

                width: visible ? height : 0;
                height: 16;
                iconSource: "dialog-warning"
                visible: WeatherApp.currentLocation.error

                onClicked: {
                    showError(WeatherApp.currentLocation.location, WeatherApp.currentLocation.errorString)
                }
            }

            PlasmaComponents.ToolButton {
                id: infoButton
                iconSource: "dialog-information"
                //text: i18n("Refresh")
                onClicked: {
                    if (infoSheet.show)
                        infoSheet.close()
                    else
                        infoSheet.open()
                }
                checked: infoSheet.show
                //width: minimumWidth + 5
                //visible: WeatherApp.currentLocation.needsRefresh && !WeatherApp.currentLocation.refreshing
            }
        }
    }


	
    Component  {
        id: tileitem
		
        Item {
            id: wrapper
			
            width: locationsSheet.width - 15
            height: locationsSheet.tileHeight
			
            WeatherTile {
                id: tile
                anchors.fill: parent
                selected: modelData.location === WeatherApp.currentLocation.location;
				
                onSelectedChanged: {
                    if (selected) {
                        wrapper.ListView.view.currentIndex = index
                    } else {
                        wrapper.ListView.view.currentIndex = -1
                    }
                }
				
                onClicked: {
                    WeatherApp.currentLocation = modelData
                    locationsSheet.close()
                }
				
                alerts: modelData.alerts.length
                title: modelData.name;
                temp: modelData.conditions.temperature;
                icon: modelData.conditions.icon;
                weather: modelData.conditions.summary;
//				maxTemp: modelData.dailyForecast.length > 0 ? modelData.dailyForecast.at(0).temperatureMax : "";
//				minTemp: modelData.dailyForecast.length > 0 ? modelData.dailyForecast.at(0).temperatureMin : "";
				
                //iconForecast: modelData.dailyForecast.length > 0 ? modelData.dailyForecast.at(0).icon : "weather-desktop";
                //weatherForecast: modelData.dailyForecast.length > 0 ? modelData.dailyForecast.at(0).summary : "No forecast available";
            }
        }
    }

    SheetDialog {
        id: infoSheet

        anchors {
            bottom: bottomToolBar.top
            right: parent.right
            margins: 4
        }

        direction: "up"

        width: column.width + 18
        height: column.height + 15

        Column {
            id: column
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -2

            spacing: 2

            Text {
                id: lastUpdatedText

                text: i18nc("The time the weather was last downloaded",
                        "Last updated at %1", Qt.formatTime(WeatherApp.currentLocation.lastUpdated))
                visible: WeatherApp.currentLocation.valid
            }

            Text {
                id: creditsText

                text: i18nc("Credits for the weather data", "Powered by <a href=\"http://forecast.io/\">Forecast.io</a>")
                textFormat: Text.RichText;
                onLinkActivated: {
                    Qt.openUrlExternally(link)
                }
            }
        }
    }

    SheetDialog {
        id: locationsSheet

        anchors {
            top: topToolBar.bottom
            left: parent.left
            margins: 4
            topMargin: 6
        }


        property int tileHeight: 72
        width: 200
        implicitHeight: searchField.height + listTools.height +
                        Math.max(list.count * (tileHeight + list.spacing) + 20, 50)
        property int maximumHeight: 350/*searchField.height + listTools.height +
                                    3 * (tileHeight + list.spacing) + 20*/
        height: Math.min(maximumHeight, implicitHeight)

        PlasmaWidgets.LineEdit {
            id: searchField;

            clickMessage: i18n("Search...")
            clearButtonShown: true
            onReturnPressed: {
                locationsSheet.close()
                WeatherApp.setLocation(text)
            }

            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                margins: 2
            }
        }

        PlasmaWidgets.Separator {
            id: separator
            anchors {
                top: searchField.bottom
                left: parent.left
                right: parent.right
                margins: 2
            }
        }

        ListView {
            id: list

            anchors {
                top: separator.bottom
                //topMargin: 5
                left: parent.left
                right: parent.right
                bottom: listTools.top
                margins: 2
            }

            interactive: locationsSheet.implicitHeight > locationsSheet.height

            clip: true
            spacing: 5

            model: WeatherApp.locations;
            delegate: tileitem;
        }

        Text {
            id: noLocationsText

            anchors.centerIn: list

            opacity: 0.5
            font.italic: true
            text: i18n("No saved locations")
            visible: list.count === 0
        }

        Column {
            id: listTools
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: 2
            }

            PlasmaWidgets.Separator {
                id: actionsSeparator
                width: parent.width - 5
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                id: listActions
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 10

                PlasmaComponents.ToolButton {
                    iconSource: "list-add"
                    onClicked: {
                        locationsSheet.close()
                        WeatherApp.addCurrentLocation()
                    }
                    enabled: WeatherApp.currentLocation === null || WeatherApp.location(WeatherApp.currentLocation.location) === null
                }

                PlasmaComponents.ToolButton {
                    iconSource: "edit-delete"
                    onClicked: {
                        locationsSheet.close()
                        WeatherApp.removeCurrentLocation()
                    }
                }
            }
        }
    }

    function getIcon(name, size) {
        var path = ""
        //print(name)

        if (size === undefined) size = 128

        if (name === "weather-clear")
            path = "Sun"
        else if (name === "weather-clear-night")
            path = "Moon"
        else if (name === "weather-clouds")
            path = "Cloud-Sun"
        else if (name === "weather-clouds-night")
            path = "Cloud-Moon"
        else if (name === "weather-many-clouds")
            path = "Cloud"
        else if (name === "weather-showers")
            path = "Cloud-Rain"
        else if (name === "weather-snow")
            path = "Cloud-Snow"
        else if (name === "weather-freezing-rain")
            path = "Cloud-Hail-Alt"
        else if (name === "weather-wind")
            path = "Wind"
        else if (name === "weather-mist")
            path = "Cloud-Fog"

        var filename = Qt.resolvedUrl("../icons/" + size + "/" + path + ".png")

        //console.log(">>>>>>>>>>>>>>>>" + filename)
        return filename
    }
}
