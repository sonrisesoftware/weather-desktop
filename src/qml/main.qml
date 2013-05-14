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
	
	property variant appStyle: Style {
		id: style
	}
	
	Image {
		id: background
		//source: "images/background.jpg"
		source: "images/weather-clear.jpg"
		anchors.fill: parent
	}
	
	Component {
        id: widgetdelegate
        Item {
            width: grid.cellWidth; height: grid.cellHeight
            WeatherTile {
                id: im
                
                anchors.centerIn: parent
                width: grid.cellWidth - 10; height: grid.cellHeight - 10
                
                title: modelData.name
                
                Rectangle {
                    id: imRect
                    anchors.fill: parent; radius: 0
                    anchors.centerIn: parent
                    border.color: "#326487"; color: "transparent"; border.width: 2;
                    opacity: 0
                }
            }
            Rectangle {
                id: iWasHere
                width: 20; height: 20; radius: 20
                smooth: true
                anchors.centerIn: parent
                color: "white";
                opacity: 0
            }
            states: [
                State {
                    name: "inDrag"
                    when: index == grid.firstIndexDrag
                    PropertyChanges { target: iWasHere; opacity: 1 }
                    PropertyChanges { target: imRect; opacity: 1 }
                    PropertyChanges { target: im; parent: container }
                    PropertyChanges { target: im; width: (grid.cellWidth - 10) / 2 }
                    PropertyChanges { target: im; height: (grid.cellHeight - 10) / 2 }
                    PropertyChanges { target: im; anchors.centerIn: undefined }
                    PropertyChanges { target: im; x: coords.mouseX - im.width/2 }
                    PropertyChanges { target: im; y: coords.mouseY - im.height/2 }
                }
            ]
            transitions: [
                Transition { NumberAnimation { properties: "width, height, opacity"; duration: 300; easing.type: Easing.InOutQuad } }
            ]
        }
    }
 
    GridView {
        property int firstIndexDrag: -1
 
        id: grid
        x: 0; y: 0
        interactive: false
 
        anchors.rightMargin: 200
        anchors.bottomMargin: 100
        anchors.leftMargin: 200
        anchors.topMargin: 100
        anchors.fill: parent
        cellWidth: 220; cellHeight: 120;
 
        model: WeatherApp.locations
        delegate: widgetdelegate
        Item {
            id: container
            anchors.fill: parent
        }
        MouseArea {
            id: coords
            anchors.fill: parent
 
            onReleased: {
				console.log("Swapping " + grid.firstIndexDrag + " with " + grid.indexAt(mouseX, mouseY))
                if (grid.firstIndexDrag != -1)
                    WeatherApp.move_location(grid.firstIndexDrag,grid.indexAt(mouseX, mouseY), 1)
                grid.firstIndexDrag = -1
            }
            onPressed: {
                grid.firstIndexDrag=grid.indexAt(mouseX, mouseY)
            }
        }
    }
}
