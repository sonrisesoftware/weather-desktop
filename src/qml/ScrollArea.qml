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
	
	width: orientation == Qt.Vertical ?
		itemWidth :// + scrollBar.width + 5 :
		itemWidth * itemCount + itemSpacing * (itemCount - 1)
	height: orientation == Qt.Vertical ?
		itemHeight * itemCount + itemSpacing * (itemCount - 1) :
		itemHeight// + scrollBar.height + 5
	
	property int itemWidth
	property int itemHeight
	property int itemCount
	property alias itemSpacing: list.spacing;
	property alias model: list.model;
	property alias delegate: list.delegate;
	property variant orientation: Qt.Vertical;
	color: "transparent";
	
	ListView {
		id: list
		
		height: itemHeight
		
		snapMode: ListView.SnapToItem
		clip: true
		orientation: root.orientation
	}
	
	ScrollBar {
		id: scrollBar
		
		orientation: root.orientation
		target: list
	}
	
	states: [
		State {
			when: orientation == Qt.Horizontal
			PropertyChanges { target: list; 
				anchors {
					top: root.top
					bottom: root.bottom
					//bottom: scrollBar.top;
					//bottomMargin: 5;
					left: root.left;
					right: root.right;
				}
			}
			PropertyChanges { target: scrollBar; 
				anchors {
					left: root.left; leftMargin: 2;
					right: root.right; rightMargin: 2;
					bottom: root.bottom;
				}
			}
		},
		State {
			when: orientation == Qt.Vertical
			PropertyChanges { target: list; 
				anchors {
					top: root.top;
					bottom: root.bottom;
					left: root.left;
					//right: scrollBar.right;
					//rightMargin: 5;
					right: root.right
				}
			}
			PropertyChanges { target: scrollBar; 
				anchors {
					top: root.top; topMargin: 2;
					bottom: root.bottom; bottomMargin: 2;
					right: root.right
				}
			}
		}
	]
}