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
	//color: "#99333333" // temporary, for visualization - will be transparent
	color: "#00000000" // transparent
	//radius: 6
	
	state: "conditions"
	
	WeatherConditions {
		id: conditions
		anchors.centerIn: root
		opacity: 0
		
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
		
		Behavior on opacity {
			NumberAnimation { duration: 500 }
		}
	}
	
	ErrorDialog {
		id: error
		opacity: 0
		anchors.centerIn: root
		title: "Unable to access weather"
		text: WeatherApp.currentLocation.errorMessage
		
		Behavior on opacity {
			NumberAnimation { duration: 500 }
		}
	}
	
	states: [
		State {
			name: "conditions"
			when: (WeatherApp.currentLocation.error != true)
			PropertyChanges { target: conditions; opacity: 1; restoreEntryValues: true; }
		},
		State {
			name: "error"
			when: (WeatherApp.currentLocation.error == true)
			PropertyChanges { target: error; opacity: 1; restoreEntryValues: true; }
		}
	]
	
	transitions: [
		Transition {
			to:	"*"
			NumberAnimation { property: "opacity"; duration: 1000 }
		}
	]
}