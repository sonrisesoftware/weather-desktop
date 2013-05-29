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

Panel {
	id: root
	
	//property Style style;
	color: Qt.rgba(0.5,0.25,0.25,0.75)
	property alias text: msg.text
	implicitWidth: Math.max(220, header.width + 20);
	implicitHeight: Math.max(160, msg.paintedHeight + 10);
	
	Text {
		id: msg
		color: appStyle.textColor
		width: 200
		wrapMode: Text.Wrap
		font.pixelSize: appStyle.headerFontSize
		anchors.centerIn: root
	}
}
