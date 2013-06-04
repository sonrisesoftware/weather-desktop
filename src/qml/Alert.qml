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
	color: appStyle.errorColor
	opacity: 0.7
	
	radius: appStyle.panelRadius;
	border.color: appStyle.borderColor;
	
	implicitWidth: 400
	height: row.implicitHeight + 2 * row.anchors.margins
	
	property variant alert
	
	Row {
		id: row
		anchors {
			margins: 2
			leftMargin: 7
			rightMargin: 7
			left: parent.left
			right: parent.right
			top: parent.top
		}
		
		Text {
			id: title
			
			text: alert.title
			
			font.pixelSize: appStyle.headerFontSize
			color: appStyle.textColor
			
			style: Text.Raised
			styleColor: appStyle.shadowColor
			anchors.verticalCenter: parent.verticalCenter
		}
		
		Item {
			height: parent.height
			width: parent.width 
					- title.width - expires.width - url.width
					- (parent.children.length - 1) * parent.spacing
		}
		
		Text {
			id: expires
			
			text: "Until " + (today ? "" : Qt.formatDateTime(alert.expires)) + Qt.formatTime(alert.expires)
			
			property bool today: Qt.formatDate(alert.expires) == Qt.formatDate(new Date())
			property bool week: new Date().date + 7 <= alert.expires.date
			
			font.pixelSize: appStyle.headerFontSize
			//font.italic: true
			color: appStyle.textColor
			
			style: Text.Raised
			styleColor: appStyle.shadowColor
			anchors.verticalCenter: parent.verticalCenter
		}
		
		PlasmaComponents.ToolButton {
			id: url
			anchors.verticalCenter: parent.verticalCenter
			visible: alert.url != ""
			
			iconSource: "go-jump-locationbar"
			
			onClicked: {
				console.log("URL: " + alert.url)
					Qt.openUrlExternally(alert.url)
			}
		}
	}
}