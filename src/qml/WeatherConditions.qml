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
	
	// FIXME: Why doesn't the WeatherPanel version work???
 	implicitWidth: Math.max(header.width + 10, left.width + right.width + 90)
 	implicitHeight: header.height + Math.max(left.height, right.height) + 40
	
	property string windchill;
	property string dewpoint;
	
	property string pressure;
	property string visibility;
	property string clouds;
	
	property string wind;
	property string windgust;
	
	property string humidity;
	property string precip;
	
	title: i18n("Current Conditions")
		
	Form {
		id: left
		fontSize: appStyle.dataFontSize
		headerSize: appStyle.headerFontSize
		color: appStyle.textColor
		
		anchors {
			top: header.bottom
			topMargin: 20
			left: root.left
			leftMargin: 20
		}
		
		FormHeader {
			text: i18n("Temperature")
		}
		
		FormItem {
			label: i18n("Feels like:")
			value: root.windchill
		}
		
		FormItem {
			label: i18n("Dew point:")
			value: root.dewpoint
		}
		
		FormItem {}
		
		FormHeader {
			text: i18n("Conditions")
		}
		
		FormItem {
			label: i18n("Pressure:")
			value: root.pressure
		}
				
		FormItem {
			label: i18n("Visibility:")
			value: root.visibility
		}
		
		FormItem {
			label: i18n("Cloud Cover:")
			value: root.clouds
		}
		
	}
	
	Form { // Right column of data
		id: right
		fontSize: appStyle.dataFontSize
		headerSize: appStyle.headerFontSize
		color: appStyle.textColor
		
		anchors {
			top: header.bottom
			topMargin: 20
			left: left.right
			leftMargin: 40
		}
		
		FormHeader {
			text: i18n("Wind")
		}
				
		FormItem {
			label: i18n("Speed/Dir:")
			value: root.wind
		}
		
		FormItem {
			label: i18n("Wind Gust:")
			value: root.windgust
		}
		
		FormItem {}
		
		FormHeader {
			text: i18n("Moisture")
		}
		
		FormItem {
			label: i18n("Humidity:")
			value: root.humidity
		}
		
		FormItem {
			label: i18n("Precipitation:")
			value: root.precip
		}
	}
}
