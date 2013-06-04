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

QtObject {
	property int dataFontSize: 14;
	property int headerFontSize: 16;
	property int titleFontSize: 18;
	property int mainTitleFontSize: 20;
	property color textColor: "white";
	//property color panelColor: "#99333333";
	property color panelColor: Qt.rgba(0.2,0.2,0.2,0.75);
	//property color borderColor: "white"
	property color borderColor: Qt.darker(panelColor, 1.4)
	//property color internalBorderColor: panelColor//Qt.lighter(panelColor, 2)
	property color internalBorderColor: Qt.darker(panelColor, 1.4)
	property color shadowColor: Qt.rgba(0,0,0,0.75)
	property int panelRadius: 6;
	property color highlightColor: Qt.rgba(0.5,0.5,0.6,0.2)
	property color errorColor: "#c31f1f"
}
