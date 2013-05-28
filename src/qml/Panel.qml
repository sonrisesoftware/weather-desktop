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
	
	implicitWidth: childrenRect.width + 50
	implicitHeight: childrenRect.height + 20
	
	color: appStyle.panelColor;
	radius: appStyle.panelRadius;
	
	border.color: appStyle.borderColor;
	
	property alias title: header.text
	property alias header: header
	//property Style style;
	
	Text {
		id: header
		color: appStyle.textColor;
		font.pixelSize: appStyle.titleFontSize
		
		style: Text.Raised
		styleColor: appStyle.shadowColor
		
		anchors { horizontalCenter: root.horizontalCenter; top: root.top; topMargin: 5 }
	}
	
	PlasmaWidgets.Separator {
		width: header.width * 3/4
		anchors { horizontalCenter: root.horizontalCenter; top: header.bottom; topMargin: 5 }
	}
}
