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
	//color: "#99333333" // temporary, for visualization - will be transparent
	color: "#00000000" // transparent
	//radius: 6
	
	property string view: "conditions"
	property bool is_error: (WeatherApp.currentLocation.error == true) && !is_updating
	property bool is_updating: (WeatherApp.currentLocation.refreshing == true)
	property bool is_regular: !(is_error || is_updating)
	
	PlasmaWidgets.BusyWidget {
		id: updating
		
		width: 100; height: 100;
		anchors.centerIn: root
		
		opacity: 0
		running: false
		//label: "Updating weather..."
	}
	
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
		precip: WeatherApp.currentLocation.conditions.precip;
		
		Behavior on opacity {
			NumberAnimation { duration: 500 }
		}
	}
	
	ErrorDialog {
		id: error
		opacity: 0
		anchors.centerIn: root
		title: i18n("Unable to access weather")
		text: WeatherApp.currentLocation.errorString;
		
		Behavior on opacity {
			NumberAnimation { duration: 500 }
		}
	}
	
	/*WeatherForecast {
		id: forecast
		anchors.centerIn: root
		opacity: 0
				
		Behavior on opacity {
			NumberAnimation { duration: 500 }
		}
	}*/
	
	states: [
		State {
			name: "conditions"
			when: is_regular && view == "conditions"
			PropertyChanges { target: conditions; opacity: 1; restoreEntryValues: true; }
			PropertyChanges { target: root; implicitWidth: conditions.implicitWidth; }
			PropertyChanges { target: root; implicitHeight: conditions.implicitHeight; }
		},
		State {
			name: "daily"
			when: is_regular && view == "daily"
			PropertyChanges { target: forecast; opacity: 1; restoreEntryValues: true; }
			PropertyChanges { target: root; implicitWidth: forecast.implicitWidth; }
			PropertyChanges { target: root; implicitHeight: forecast.implicitHeight; }
		},
		State {
			name: "error"
			when: is_error
			PropertyChanges { target: error; opacity: 1; restoreEntryValues: true; }
			PropertyChanges { target: root; implicitWidth: error.implicitWidth; }
			PropertyChanges { target: root; implicitHeight: error.implicitHeight; }
		},
		State {
			name: "updating"
			when: is_updating
			PropertyChanges { target: updating; opacity: 1; running: true; restoreEntryValues: true; }
			PropertyChanges { target: root; implicitWidth: updating.width; }
			PropertyChanges { target: root; implicitHeight: updating.height; }
		}
	]
	
	transitions: [
		Transition {
			to:	"*"
			NumberAnimation { property: "opacity"; duration: 750 }
		}
	]
}
