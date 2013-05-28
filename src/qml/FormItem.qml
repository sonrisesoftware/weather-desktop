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

Item {
	id: root
	
	property alias label: label.text;
	property alias value: value.text;
	property int align: label.width + root.indent;
	property alias valueWidth: value.width;
	property int indent: root.parent.indent;
	implicitHeight: childrenRect.height;
	implicitWidth: childrenRect.width;
	opacity: value.text == "" && label.text != "" ? 0 : 1
	
	Text {
		id: label
		x: root.indent;
		color: root.parent.color;
		style: Text.Raised
		styleColor: appStyle.shadowColor
		font.pixelSize: root.parent.fontSize;
	}
	
	Text {
		id: value
		
		x: root.parent.align
		color: root.parent.color;
		style: Text.Raised
		styleColor: appStyle.shadowColor
		font.pixelSize: root.parent.fontSize;
	}
}
