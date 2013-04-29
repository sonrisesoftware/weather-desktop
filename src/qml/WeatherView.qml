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
	color: "#99333333" // temporary, for visualization - will be transparent
	//color: "#00000000" // transparent
	radius: 6
	implicitWidth: childrenRect.width
	implicitHeight: childrenRect.height
	
	state: "conditions"
	
	WeatherConditions {
		id: conditions
		anchors.centerIn: root
		visible: false
		
		windchill: WeatherApp.currentLocation.conditions.windchill;
		dewpoint: WeatherApp.currentLocation.conditions.dewpoint;
		
		pressure: WeatherApp.currentLocation.conditions.pressure;
		visibility: WeatherApp.currentLocation.conditions.visibility;
		clouds: WeatherApp.currentLocation.conditions.clouds;
		
		wind: WeatherApp.currentLocation.conditions.wind;
		windgust: WeatherApp.currentLocation.conditions.windgust;
		
		humidity: WeatherApp.currentLocation.conditions.humidity;
		rainfall: WeatherApp.currentLocation.conditions.rainfall;
		snowdepth: WeatherApp.currentLocation.conditions.snowdepth;
	}
	
	Text {
		id: error
		anchors.centerIn: root
		visible: false
		width: 200
		wrapMode: Text.Wrap
		text: "<b>Unable to access weather:</b><p><p>" + WeatherApp.currentLocation.errorMessage
	}
	
	Behavior on implicitHeight {
		NumberAnimation {
             easing {
                 type: Easing.OutElastic
                 amplitude: 1.0
                 period: 0.5
             }
         }
	}
	
	Behavior on implicitWidth {
		NumberAnimation {
             easing {
                 type: Easing.OutElastic
                 amplitude: 1.0
                 period: 0.5
             }
         }
	}
	
	states: [
		State {
			name: "conditions"
			when: (WeatherApp.currentLocation.error != true)
			PropertyChanges { target: conditions; visible: true; restoreEntryValues: true; }
			PropertyChanges { target: root;  color: "#99333333"; restoreEntryValues: true; }
		},
		State {
			name: "error"
			when: (WeatherApp.currentLocation.error == true)
			PropertyChanges { target: error; visible: true; restoreEntryValues: true; }
			PropertyChanges { target: root;  color: Qt.rgba(0.5,0.25,0.25,0.75); restoreEntryValues: true; }
		}
	]
	
	/*transitions: [
		Transition {
			from 
			NumberAnimation { properties: "root.scale"; from: 0; to: 1; duration: 200; easing {type: Easing.OutBack; overshoot: 500} }
		}		
	]*/
}