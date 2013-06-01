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

Panel {
	id: root
	
	implicitWidth: Math.max(header.width + 10, contents.width + 20)
	implicitHeight: header.height + contents.height + 30
	
	property int tileWidth: 500
	property int tileHeight: 24
	property int tileCount: 7
	
	property variant weatherLocation
	
	title: "Hourly Forecast"
	
	Component {
		id: dayForecast
		
		Item {
			id: dayItem
			
			property variant modelData: weatherLocation.hourlyForecast.at(index)
			property bool last: index == (view.model - 1)
			
			width: tileWidth
			height: tileHeight
			
			Rectangle {
				visible: !last
				opacity: 0.5
				width: parent.width
				height: 1
				color: appStyle.borderColor
			
				anchors {
					bottom: dayItem.bottom
					bottomMargin: -view.itemSpacing/2
				}
			}
			
			Row {
				anchors.fill: parent
				anchors.leftMargin: 2
				
				spacing: 10
				
				Text {
					id: title
					anchors.verticalCenter: parent.verticalCenter;
					
					text: Qt.formatTime(modelData.time)
					width: 120
					
					font.pixelSize: appStyle.headerFontSize
					color: appStyle.textColor
					
					style: Text.Raised
					styleColor: appStyle.shadowColor
					elide: Text.ElideRight
				}
				
				PlasmaCore.IconItem {
					id: weatherIcon
					source: modelData.icon;
					width: 24;
					height: 24;
					
					anchors.verticalCenter: parent.verticalCenter;
				}
				
				Item {
					width: 30
					height: parent.height;
				}
				
				Text {
					id: precipProbability
					
					width: 30
					text: modelData.precipProbability || "0%"
					horizontalAlignment: Text.AlignHCenter
					font.pixelSize: appStyle.headerFontSize
					color: appStyle.textColor
					
					style: Text.Raised
					styleColor: appStyle.shadowColor
					anchors.verticalCenter: parent.verticalCenter;
				}
				
				Item {
					width: 30
					height: parent.height;
				}
				
				Text {
					id: temp
					
					width: 30
					text: modelData.temperature
					horizontalAlignment: Text.AlignHCenter
					font.pixelSize: appStyle.headerFontSize
					color: appStyle.textColor
					
					style: Text.Raised
					styleColor: appStyle.shadowColor
					anchors.verticalCenter: parent.verticalCenter;
				}
				
				Item {
					width: 30
					height: parent.height;
				}
				
				Text {
					id: summary
					
					text: modelData.summary
					font.pixelSize: appStyle.headerFontSize
					color: appStyle.textColor
					elide: Text.ElideRight
					
					style: Text.Raised
					styleColor: appStyle.shadowColor
					anchors.verticalCenter: parent.verticalCenter;
				}
			}
		}
	}
	
	
	Column {
		id: contents
		anchors {
			bottom: parent.bottom;
			bottomMargin: 5;
			horizontalCenter: parent.horizontalCenter;
		}
		
		Row {
			anchors.leftMargin: 2
			anchors.left: parent.left
			
			spacing: 10
			
			Text {
				id: headerTitle
				anchors.verticalCenter: parent.verticalCenter;
				
				text: "Time"
				width: 120
				
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				elide: Text.ElideRight
			}
			
			Text {
				id: headerIcon
				
				width: 24
				text: "Weather"
				font.pixelSize: appStyle.dataFontSize
				horizontalAlignment: Text.AlignHCenter
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				
				anchors.verticalCenter: parent.verticalCenter;
			}
			
			Item {
				width: 30
				height: parent.height;
			}
			
			Text {
				id: headerProbability
				
				width: 30
				text: "Probability"
				horizontalAlignment: Text.AlignHCenter
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				anchors.verticalCenter: parent.verticalCenter;
			}
			
			Item {
				width: 30
				height: parent.height;
			}
			
			Text {
				id: headerTemp
				
				width: 30
				text: "Temp"
				horizontalAlignment: Text.AlignHCenter
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				anchors.verticalCenter: parent.verticalCenter;
			}
			
			Item {
				width: 30
				height: parent.height;
			}
			
			Text {
				id: summary
				
				text: "Summary"
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				elide: Text.ElideRight
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				anchors.verticalCenter: parent.verticalCenter;
			}
		}
		
		Rectangle {
			opacity: 0.5
			width: parent.width
			height: 1
			color: appStyle.borderColor
		}
		
		ScrollArea {
			id: view
			
			//border.color: appStyle.borderColor;
			//radius: 3;
			itemWidth: tileWidth
			itemHeight: tileHeight
			itemSpacing: 5
			itemCount: tileCount
			model: Math.min(weatherLocation.hourlyForecast.length, 24)
			delegate: dayForecast
		}
	}
}