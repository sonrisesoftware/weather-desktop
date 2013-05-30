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

Rectangle {
    id: root

    property alias contents: view.children
    property color highlightColor
    property alias title: header.text
    property alias font: header.font
    property alias style: header.style
    property alias styleColor: header.styleColor
    property alias titleColor: header.color

    radius: 3
    color: mouseArea.containsMouse ? highlightColor : "transparent"


    height: opener.height + 2 + dropDown.height
    width: implicitWidth
    implicitWidth: Math.max(opener.implicitWidth, dropDown.width)

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: opener

        onClicked: {
            dropDown.open = !dropDown.open
        }
    }

    Row {
        id: opener
        anchors {
            left: parent.left;
            right: parent.right;
            top: parent.top;
            margins: 3;
            topMargin: 1;
        }

        Text {
            id: header
            anchors.verticalCenter: parent.verticalCenter
        }

        Item {
            height: parent.height
            width: parent.width
                    - header.width
                    - icon.width
                    - (parent.children.length - 1) * parent.spacing
        }

        PlasmaCore.IconItem {
            id: icon
            anchors.verticalCenter: parent.verticalCenter

            width: 16; height: 16;
            source: "draw-arrow-forward";
            rotation: dropDown.open ? 90 : 0

            Behavior on rotation {
                NumberAnimation { duration: 250 }
            }
        }
    }

    Item {
        id: dropDown
        clip: true

        anchors {
            left: parent.left;
            right: parent.right;
            top: opener.bottom;
            topMargin: 2
        }
        height: open ? view.height : 0

        property bool open: false

        Behavior on height {
            NumberAnimation { duration: 250 }
        }

        Item {
            id: view
            y: parent.height-height
            height: childrenRect.height + 5
            width: childrenRect.width
        }
    }
}
