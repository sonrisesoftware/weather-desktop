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
	height: 5
	smooth: true
	
	anchors {
		left: target.left
		right: target.right
		margins: 2
	}
	
	
	Rectangle {
		id: scrollBar
		color: "black"//"white"
		opacity: 0.3
		radius: height/2
		
		anchors {
			top: root.top
			bottom: root.bottom
		}
		
		width: end - x
		
		x: Math.max(0, root.width * target.contentX/target.contentWidth)
		property int end: Math.min(root.width, root.width * (target.contentX + root.width)/target.contentWidth)

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
