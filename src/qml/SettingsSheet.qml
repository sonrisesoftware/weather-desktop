import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.graphicswidgets 0.1 as PlasmaWidgets

Rectangle {
    id: settingsSheet
    color: Qt.rgba(0,0,0,0.7)
    opacity: show ? 1 : 0

    Behavior on opacity {
        NumberAnimation {
            duration: 250;
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
    }

    signal opened
    signal closed

    property bool show: false

    function open() {
        show = true
        dialog.open()
        opened()
    }

    function close() {
        show = false
        dialog.close()
        closed()
    }

    function isOpen() {
        return root.state == "open"
    }

    SheetDialog {
        id: dialog
        anchors.centerIn: parent

        width: 500
        height: 300
//        show: true

        Text {
            id: header
            text: i18n("Settings")

            font.pixelSize: appStyle.titleFontSize

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 5
            }
        }

        PlasmaWidgets.Separator {
            anchors {
                left: parent.left
                right: parent.right
                horizontalCenter: parent.horizontalCenter; top: header.bottom; topMargin: 5
            }
        }

        PlasmaComponents.Button {
            anchors {
                bottom: parent.bottom
                right: parent.right
                margins: 5
            }

            width: 80

            text: i18n("Close")
            onClicked: {
                settingsSheet.close()
            }
        }
    }
}
