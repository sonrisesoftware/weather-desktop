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
	id: root;
	
	color: highlighted ? Qt.darker(appStyle.panelColor, 2) : appStyle.panelColor
	border.color: appStyle.internalBorderColor;
	property color textColor: appStyle.textColor;
	
	smooth: true
	width: 200
	height: 100
	
	signal clicked
	
	property alias icon: icon.source;
	property alias title: title.text;
	property alias temp: temp.text;
	property alias weather: weather.text;
	property alias iconForecast: iconForecast.source;
	//property alias tempForecast: tempForecast.text;
	property alias weatherForecast: weatherForecast.text;
	
	property bool alert: false;
	property bool selected: false;
	property bool highlighted: selected || state == "mouse-over"
	
	Text {
		id: title
		
		anchors {
			top: root.top;
			left: root.left;
			leftMargin: 5;
			topMargin: 2;
		}
		
		font.pixelSize: appStyle.titleFontSize;
		color: textColor;
		style: Text.Raised
		styleColor: appStyle.shadowColor
	}
	
	PlasmaCore.IconItem {
		id: alertIcon
		source: root.alert ? "emblem-important" : ""
		width: 16; height: 16;
		
		anchors {
			top: parent.top;
			right: parent.right;
			topMargin: 5;
			rightMargin: 5;
		}
	}
	
	Item {
		id: conditions
		opacity: 0
		
		anchors {
			top: title.bottom;
			bottom: root.bottom;
			left: root.left;
			right: root.right;
		}
	
		PlasmaCore.IconItem {
			id: icon
			width: 64; height: 64;
			
			anchors {
				left: parent.left;
				leftMargin: 10;
				verticalCenter: parent.verticalCenter;
			}
		}
		
		Text {
			id: temp
			
			anchors {
				left: icon.right;
				leftMargin: 10;
				bottom: parent.verticalCenter;
			}
			
			font.pixelSize: appStyle.titleFontSize;
			color: textColor;
			style: Text.Raised
			styleColor: appStyle.shadowColor
		}
		
		Text {
			id: weather
			
			anchors {
				left: icon.right;
				leftMargin: 10;
				top: parent.verticalCenter;
				right: parent.right;
				rightMargin: 10;
			}
			
			font.pixelSize: appStyle.headerFontSize - 2;
			elide: Text.ElideRight;
			color: textColor;
			style: Text.Raised
			styleColor: appStyle.shadowColor
		}
	}
	
	Item {
		id: forecast
		opacity: 0
		
		anchors {
			top: title.bottom;
			bottom: root.bottom;
			left: root.left;
			right: root.right;
		}
		
		PlasmaCore.IconItem {
			id: iconForecast
			width: 64; height: 64;
			
			anchors {
				left: parent.left;
				leftMargin: 10;
				verticalCenter: parent.verticalCenter;
			}
		}
		
		/*Text {
			id: tempForecast
			
			anchors {
				left: iconForecast.right;
				leftMargin: 10;
				bottom: parent.verticalCenter;
			}
			
			font.pixelSize: appStyle.titleFontSize;
			color: textColor;
		}*/
		
		Text {
			id: weatherForecast
			
			anchors {
				left: iconForecast.right;
				leftMargin: 10;
				right: parent.right;
				rightMargin: 10;
				//top: iconForecast.top;//parent.verticalCenter;
				//bottom: iconForecast.bottom;
				verticalCenter: iconForecast.verticalCenter;
			}
			
			font.pixelSize: appStyle.headerFontSize - 2;
			color: textColor;
			style: Text.Raised
			styleColor: appStyle.shadowColor
			//elide: Text.ElideRight;
			wrapMode: Text.Wrap;
			textFormat: Text.PlainText
		}
	}
	
	Behavior on color {
		ColorAnimation { duration: 300 }
	}
	
	MouseArea {
		id: mouseArea
		hoverEnabled: true
		anchors.fill: parent
		onClicked: root.clicked()
	}
	
	states: [
		State {
			name: "default"
			when: !mouseArea.containsMouse
			PropertyChanges { target: conditions; opacity: 1; restoreEntryValues: true; }
		},	
		State {
			name: "mouse-over"
			when: mouseArea.containsMouse
			PropertyChanges { target: forecast; opacity: 1; restoreEntryValues: true; }
		}
	]
	
	transitions: [
		Transition {
			to:	"*"
			NumberAnimation { property: "opacity"; duration: 300 }
		}
	]
}
