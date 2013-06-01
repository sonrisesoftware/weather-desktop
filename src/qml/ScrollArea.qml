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
	
	width: itemWidth * itemCount + itemSpacing * (itemCount - 1)
	height: itemHeight// + scrollBar.height + 5;
	
	property int itemWidth
	property int itemHeight
	property int itemCount
	property alias itemSpacing: list.spacing;
	property alias model: list.model;
	property alias delegate: list.delegate
	
	ListView {
		id: list
		anchors {
			top: parent.top
			bottom: parent.bottom;//scrollBar.top;
			//bottomMargin: 5;
			left: parent.left;
			right: parent.right;
		}
		
		height: itemHeight
		
		snapMode: ListView.SnapToItem
		clip: true
		orientation: Qt.Horizontal
	}
	
	ScrollBar {
		id: scrollBar
		
		anchors {
			left: parent.left; leftMargin: 2;
			right: parent.right; rightMargin: 2;
			bottom: parent.bottom;
		}
		
		orientation: Qt.Horizontal
		target: list
	}
}