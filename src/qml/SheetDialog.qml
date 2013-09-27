/*
 *  Copyright 2012  Sebastian Gottfried <sebastiangottfried@web.de>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore

Item {
    id: root

    default property alias content: contentArea.children
    property int innerMargin: 5
    signal opened
    signal closed

    property bool show: false

    function open() {
        show = true
        opened()
    }

    function close() {
        show = false
        closed()
    }

    function isOpen() {
        return root.state == "open"
    }

    clip: true

    /* swallow all mouse events */
//    MouseArea {
//        anchors.fill: root.parent
//        hoverEnabled: true
//        onClicked: close()
//    }

    Item {
        id: slider
        width: parent.width
        height: show ? parent.height : 0//parent.height/2
        //anchors.centerIn: parent

        Behavior on height {
            NumberAnimation { duration: 250 }
        }

        opacity: show ? 1 : 0

        Behavior on opacity {
            NumberAnimation { duration: 250 }
        }

        PlasmaCore.FrameSvgItem  {
            id: frame
            anchors {
                fill: parent
//                leftMargin: 10
//                rightMargin: 10
//                bottomMargin: 10
            }
            imagePath: "widgets/frame"
            prefix: "raised"

//        }

//        PlasmaCore.FrameSvgItem {
//            anchors {
//                fill: parent
//                leftMargin: 10
//                rightMargin: 10
//                bottomMargin: 10
//            }
//            imagePath: "dialogs/background"
//            enabledBorders: PlasmaCore.FrameSvg.LeftBorder + PlasmaCore.FrameSvg.RightBorder + PlasmaCore.FrameSvg.BottomBorder + PlasmaCore.FrameSvg.TopBorder

            Item {
                id: contentArea
                anchors {
                    fill: parent
                    leftMargin: innerMargin
                    rightMargin: innerMargin
                    topMargin: innerMargin
                    bottomMargin: innerMargin
                }

                clip: true
            }
        }
    }
}
