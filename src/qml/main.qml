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
	implicitWidth: appview.implicitWidth
	implicitHeight: appview.implicitHeight
	
	property variant appStyle: Style {
		id: style
	}
	
	function showError(location, error) {
		WeatherApp.showError("<b>" + location + "</b>:<p><p>" + error)
	}
	
	AppView {
		id: appview
		
		opacity: WeatherApp.showWelcomeScreen ? 0 : 1
		
		Behavior on opacity {
			NumberAnimation { duration: 1500 }
		}
	}
	
	Item {
		id: startupScreen
		anchors.fill: parent
		
		Image {
			id: startupImage
			source: "../images/weather-clear.jpg"
			anchors.fill: parent
		}
		
		Column {
			
			anchors.centerIn: parent
			
			PlasmaCore.IconItem {
				id: statupIcon
				anchors.horizontalCenter: parent.horizontalCenter
				
				source: "weather-desktop"
				width: 128; height: 128;
			}
			
			Text {
				id: statupTitle
				anchors.horizontalCenter: parent.horizontalCenter
				
				color: appStyle.textColor;
				font.pixelSize: 1.2 * appStyle.titleFontSize
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				
				text: i18n("Weather Desktop")
			}
		}
		
		opacity: WeatherApp.showWelcomeScreen ? 1 : 0
		
		Behavior on opacity {
			NumberAnimation { duration: 1500 }
		}
	}
}
