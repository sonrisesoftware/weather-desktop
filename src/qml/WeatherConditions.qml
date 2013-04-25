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

Rectangle {
	id: root
	
	color: "#99333333"
	radius: 4
	
	implicitWidth: Math.max(header.width + 10, contents.width + 40)
	implicitHeight: header.height + contents.height + 40
	
	property string windchill;
	property string dewpoint;
	
	property string pressure;
	property string visibility;
	property string clouds;
	
	property string wind;
	property string windgust;
	
	property string humidity;
	property string rainfall;
	property string snowdepth;
	
	property int dataFontSize: 14;
	property int headerFontSize: 16;
	property int titleFontSize: 18;
	
	Text {
		id: header
		text: i18n("Current Conditions")
		color: "white"
		font.pixelSize: root.titleFontSize
		
		anchors { horizontalCenter: root.horizontalCenter; top: root.top;}
	}
	
	Item {
		id: contentBox
		anchors {
			top: header.bottom; topMargin: 20;
			bottom: root.bottom; bottomMargin: 20;
			left: root.left; leftMargin: 0;
			right: root.right; rightMargin: 20;
		}
	
		Row {
			id: contents
			spacing: 60
			
			anchors {
				centerIn: contentBox
			}
			
			Column { // Left column of data
				Text {
					text: i18n("Temperature")
					color: "white"
					font.pixelSize: root.headerFontSize
				}
				
				Row {
					x: 15
					spacing: 5
					
					Column { // The headers
						
						Text {
							text: i18n("Windchill:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: i18n("Dew point:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
					}
					
					Column { // The actual data
						Text {
							text: root.windchill
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: root.dewpoint
							color: "white"
							font.pixelSize: root.dataFontSize
						}
					}
				}
				
				Text {
					text: " "
				}
				
				Text {
					text: i18n("Conditions")
					color: "white"
					font.pixelSize: root.headerFontSize
				}
				
				Row {
					x: 15
					spacing: 5
					
					Column { // The headers
						
						Text {
							text: i18n("Pressure:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: i18n("Visibility:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: i18n("Cloud Cover:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
					}
					
					Column { // The actual data
						Text {
							text: root.pressure
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: root.visibility
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: root.clouds
							color: "white"
							font.pixelSize: root.dataFontSize
						}
					}
				}
			}
			
			Column { // Right column of data
				Text {
					text: i18n("Wind")
					color: "white"
					font.pixelSize: root.headerFontSize
				}
				
				Row {
					x: 15
					spacing: 5
					
					Column { // The headers
						
						Text {
							text: i18n("Speed/Dir:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: i18n("Wind Gust:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
					}
					
					Column { // The actual data
						Text {
							text: root.wind
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: root.windgust
							color: "white"
							font.pixelSize: root.dataFontSize
						}
					}
				}
				
				Text {
					text: " "
				}
				
				Text {
					text: i18n("Moisture")
					color: "white"
					font.pixelSize: root.headerFontSize
				}
				
				Row {
					x: 15
					spacing: 5
					
					Column { // The headers
						
						Text {
							text: i18n("Humidity:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: i18n("Rainfall:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: i18n("Snow depth:")
							color: "white"
							font.pixelSize: root.dataFontSize
						}
					}
					
					Column { // The actual data
						Text {
							text: root.humidity
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: root.rainfall
							color: "white"
							font.pixelSize: root.dataFontSize
						}
						
						Text {
							text: root.snowdepth
							color: "white"
							font.pixelSize: root.dataFontSize
						}
					}
				}
			}
		}
	}
}