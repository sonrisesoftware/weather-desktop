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
	
	title: "Hourly Forecast"
	
	PlasmaCore.IconItem {
		id: leftIcon
		source: "draw-arrow-back";
		width: 16;
		height: 16;
		opacity: 0;
		
		anchors {
			left: root.left
			leftMargin: 10
			verticalCenter: view.verticalCenter
		}
		
		SequentialAnimation {
			id: leftAnimation
			loops: 3;
			NumberAnimation { target: leftIcon; property: "opacity"; from: 0; to: 1; duration: 1000; easing.type: Easing.InOutQuad; }
			NumberAnimation { target: leftIcon; property: "opacity"; from: 1; to: 0; duration: 1000; easing.type: Easing.InOutQuad; }
		}
	}
	
	PlasmaCore.IconItem {
		id: rightIcon
		source: "draw-arrow-forward";
		width: 16;
		height: 16;
		opacity: 0;
		
		anchors {
			right: root.right
			rightMargin: 10
			verticalCenter: view.verticalCenter
		}
		
		SequentialAnimation {
			id: rightAnimation
			loops: 3;
			NumberAnimation { target: rightIcon; property: "opacity"; from: 0; to: 1; duration: 1000; easing.type: Easing.InOutQuad; }
			NumberAnimation { target: rightIcon; property: "opacity"; from: 1; to: 0; duration: 1000; easing.type: Easing.InOutQuad; }			
		}
	}
	
	onOpacityChanged: {
		if (opacity == 1) {
			leftAnimation.stop()
			rightAnimation.stop()
			leftAnimation.start()
			rightAnimation.start()
		} else if (opacity == 0) {
			leftAnimation.stop()
			rightAnimation.stop()
		}
	}
	
	Component {
		id: dayForecast
		
		Item {
			id: dayItem
			
			property variant modelData: weatherLocation.hourlyForecast.at(index)
			property bool last: index == (view.model - 1)
			//color: Qt.rgba(33/256,126/256,205/256,0.5)
			width: tileWidth
			height: tileHeight
			
			//PlasmaWidgets.Separator {
			Rectangle {
				visible: !last
				opacity: 0.5
				height: parent.height	
				width: 1
				color: appStyle.borderColor
				//orientation: Qt.Vertical
				anchors {
					right: dayItem.right
					rightMargin: -view.itemSpacing/2
				}
			}
			
			Text {
				id: title
				//width: parent.width - 10
				
				text: Qt.formatTime(modelData.time)
				
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
				id: weatherIcon
				source: modelData.icon;
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
				
				text: modelData.precipProbability || "0%"
				font.pixelSize: appStyle.dataFontSize
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
				
				anchors {
					topMargin: 42
					top: weatherIcon.bottom
					horizontalCenter: parent.horizontalCenter
				}
			}
				
			Text {
				id: temp
				anchors {
					//topMargin: 10
					//top: probability.bottom
					bottom: summary.top
					bottomMargin: 5
					horizontalCenter: parent.horizontalCenter
				}
				
				text: modelData.temperature
				font.pixelSize: appStyle.dataFontSize + 10
				color: appStyle.textColor
				
				style: Text.Raised
				styleColor: appStyle.shadowColor
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
		
		itemWidth: tileWidth
		itemHeight: tileHeight
		itemSpacing: 5
		itemCount: 5
		model: Math.min(weatherLocation.hourlyForecast.length, 24)
		delegate: dayForecast
	}
}