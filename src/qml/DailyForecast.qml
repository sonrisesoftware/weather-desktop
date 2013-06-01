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
	
	implicitWidth: Math.max(header.width + 10, view.width + 20)
	implicitHeight: header.height + view.height + 30
	
	property int tileWidth: 120
	property int tileHeight: 190
	property int tileCount: 5
	
	property variant weatherLocation

	title: "Daily Forecast"
	
	Component {
		id: dayForecast
		
		Item {
			id: dayItem
			
			property variant modelData: weatherLocation.dailyForecast.at(index)
			property bool last: index == (view.model - 1)
			width: tileWidth
			height: tileHeight
			
			Rectangle {
				visible: !last
				opacity: 0.5
				height: parent.height	
				width: 1
				color: appStyle.borderColor
				anchors {
					right: dayItem.right
					rightMargin: -view.itemSpacing/2
				}
			}
			
			Text {
				id: title
				//width: parent.width - 10
				
				text: today ? "Today" : Qt.formatDate(modelData.time, "dddd")
				//font.bold: true
				property bool today: Qt.formatDate(modelData.time) == Qt.formatDate(new Date())
				
				font.pixelSize: appStyle.headerFontSize
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				
				anchors {
					topMargin: 10
					top: parent.top
					horizontalCenter: parent.horizontalCenter
				}
			}
			
			PlasmaCore.IconItem {
				id: icon
				source: modelData.icon
				width: 64;
				height: 64;
				
				anchors {
					topMargin: 10
					top: title.bottom
					horizontalCenter: parent.horizontalCenter
				}
			}
			
			Text {
				id: probability
				//width: parent.width - 10
				
				text: modelData.precipProbability
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				
				anchors {
					topMargin: 42
					top: icon.bottom
					horizontalCenter: parent.horizontalCenter
				}
			}
			
			Item {
				anchors {
					topMargin: 10
					top: probability.bottom
					bottomMargin: 5
					bottom: summary.top
					left: parent.left
					leftMargin: 10
					right: parent.horizontalCenter
					rightMargin: 0
				}
				
				Text {
					id: low
					anchors.centerIn: parent
					
					text: modelData.temperatureMin
					font.pixelSize: appStyle.dataFontSize + 2
					color: "#217ecd"//appStyle.textColor
					
					style: Text.Raised
					styleColor: appStyle.shadowColor
				}
			}
			
			Item {
				anchors {
					topMargin: 10
					top: probability.bottom
					bottom: summary.top
					bottomMargin: 5
					left: parent.horizontalCenter
					rightMargin: 10
					leftMargin: 0
					right: parent.right
				}
				
				Text {
					id: high
					anchors.centerIn: parent
					
					text: modelData.temperatureMax
					font.pixelSize: appStyle.dataFontSize + 8
					color: "#c31f1f"//appStyle.textColor
					
					style: Text.Raised
					styleColor: appStyle.shadowColor
				}
			}
			
			Text {
				id: summary
				//width: parent.width - 10
				
				text: modelData.precip
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				
				//wrapMode: Text.Wrap
				
				anchors {
					bottomMargin: 10
					bottom: parent.bottom
					horizontalCenter: parent.horizontalCenter
				}
			}
		}
	}
	
	ScrollArea {
		id: view
		anchors {
			bottom: parent.bottom;
			bottomMargin: 5;
			left: parent.left;
			right: parent.right;
			leftMargin: 10;
			rightMargin: 10;
		}
		
		orientation: Qt.Horizontal
		itemWidth: tileWidth
		itemHeight: tileHeight
		itemSpacing: 5
		itemCount: 5
		model: weatherLocation.dailyForecast.length
		delegate: dayForecast
	}
}