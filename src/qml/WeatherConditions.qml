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
import org.kde.plasma.graphicswidgets 0.1 as PlasmaWidgets
import org.kde.qtextracomponents 0.1

Rectangle {
	id: root
	
	color: "#99333333"
	radius: 4
	
	implicitWidth: 600
	implicitHeight: 400
	
	property string windchill;
	property string dewpoint;
	
	Text {
		id: header
		text: "Current Conditions"
		color: "white"
		font.pixelSize: 18
		
		anchors { horizontalCenter: root.horizontalCenter; top: root.top;}
	}
	
	Row {
		anchors {
			top: header.bottom; bottom: root.bottom; 
			left: root.left; right: root.right; 
			leftMargin: 5; rightMargin: 5;
		}
		
		Column { // Left column of data
			Text {
				text: "Temperature"
				color: "white"
				font.pixelSize: 16
			}
			
			Row {
				x: 15
				spacing: 5
				
				Column { // The headers
					
					Text {
						text: "Windchill: "
						color: "white"
						font.pixelSize: 12
					}
					
					Text {
						text: "Dew point: "
						color: "white"
						font.pixelSize: 12
					}
				}
				
				Column { // The actual data
					Text {
						text: root.windchill
						color: "white"
						font.pixelSize: 12
					}
					
					Text {
						text: root.dewpoint
						color: "white"
						font.pixelSize: 12
					}
				}
			}
		}
		
		Column { // Right column of data
			
		}
	}
	
/*
 *	Temperature                    ??????????
 *      Row
 */
}