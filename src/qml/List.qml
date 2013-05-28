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
	clip: true
	
	property alias model: list.model;
	property alias delegate: list.delegate;
	property alias spacing: list.spacing;
	property alias orientation: list.orientation;
	
	ListView {
		id: list
		anchors.fill
		/*anchors {
			left: parent.left;
			top: parent.top;
			topMargin: 5;
			right: parent.right;
			bottom: parent.bottom;
			bottomMargin: 5;
		}*/
	}
	
	/*Rectangle {
		id: top
		anchors {
			left: parent.left;
			right: parent.right;
			top: parent.top;
		}
		
		height: list.atYBeginning ? 0 : 20
		
		gradient: Gradient {
			GradientStop { position: 0.0; color: listPanel.color }
			GradientStop { position: 1.0; color: "transparent" }
		}
		
		Behavior on height {
			NumberAnimation { duration: 300; easing.type: Easing.OutQuad; easing.amplitude: 2.0; easing.period: 1.5 }
		}
	}

	Rectangle {
		id: bottom
		anchors {
			left: parent.left;
			right: parent.right;
			bottom: parent.bottom;
		}
		
		height: list.atYEnd ? 0 : 20
		
		Behavior on height {
			NumberAnimation { duration: 300; easing.type: Easing.OutQuad; easing.amplitude: 2.0; easing.period: 1.5 }
		}
		
		gradient: Gradient {
			GradientStop { position: 0.0; color: "transparent" }
			GradientStop { position: 1.0; color: listPanel.color }
		}
	}*/
}

