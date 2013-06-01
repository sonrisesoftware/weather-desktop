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
	
Item {
	id: root
	property variant target
	
	clip: true
	smooth: true
	
	property variant orientation: Qt.Vertical
	property int thickness: 5
	
	onOrientationChanged: {
		if (orientation == Qt.Vertical) {
			width = thickness
		} else {
			height = thickness
		}
	}
	
	Rectangle {
		id: scrollBar
		color: "black"//"white"
		opacity: 0.3
		radius: thickness/2
		
		width: orientation == Qt.Horizontal ? end - start : thickness
		height: orientation == Qt.Vertical ? end - start : thickness
		x: orientation == Qt.Horizontal ? start : 0
		y: orientation == Qt.Vertical ? start : 0
		
		property int length: orientation == Qt.Vertical ? root.height : root.width;
		property int targetLength: orientation == Qt.Vertical ? target.height : target.width;
		property int contentStart: orientation == Qt.Vertical ? target.contentY : target.contentX;
		property int contentLength: orientation == Qt.Vertical ? target.contentHeight : target.contentWidth;
		
		property int start: Math.max(0, length * contentStart/contentLength);
		property int end: Math.min(length, length * (contentStart + targetLength)/contentLength)

		states: [
			State {
				name: "default"
				when: !target.moving
				PropertyChanges { target: scrollBar; opacity: 0; restoreEntryValues: true; }
			}, 
			State {
				name: "moving"
				when: target.moving
				PropertyChanges { target: scrollBar; opacity: 0.3; restoreEntryValues: true; }
			}
		]
		
		transitions: [
			Transition {
				to:	"moving"
				NumberAnimation { property: "opacity"; duration: 500 }
			},
			Transition {
				to:	"default"
				NumberAnimation { property: "opacity"; duration: 1500 }
			}
		]
	}
}
