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

    title: i18n("Currently")
    implicitWidth: Math.max(header.width + 10, contents.width + 20)
    implicitHeight: header.height + contents.height + 30

    property variant weatherLocation

    property variant conditions: weatherLocation.conditions;

    Column {
        id: contents

        width: topRow.width

        anchors {
            left: parent.left
            leftMargin: 10
            top: header.bottom
            topMargin: 15
        }

        spacing: 3

        Row {
            id: topRow

            spacing: 25

            Image {
                id: icon
                anchors.verticalCenter: parent.verticalCenter

                width: 128; height: 128;
                source: getIcon(conditions.icon);

//                Rectangle {
//                    color: "transparent"
//                    border.color: "white"
//                    anchors.fill: icon
//                }
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    id: temp

                    text: conditions.temperature
                    font.pixelSize: appStyle.titleFontSize * 3;
                    smooth: true
                    color: appStyle.textColor

                    style: Text.Raised
                    styleColor: appStyle.shadowColor
                }

                Text {
                    id: summary
                    width: 150

                    text: conditions.summary
                    wrapMode: Text.Wrap
                    font.pixelSize: 1.2 * appStyle.headerFontSize;
                    color: appStyle.textColor

                    style: Text.Raised
                    styleColor: appStyle.shadowColor
                }
            }
        }

        DropDown {
            id: conditionsDropDown

            width: Math.max(parent.width, implicitWidth)

            title: i18n("Conditions")
            font.pixelSize: appStyle.headerFontSize;
            titleColor: appStyle.textColor

            style: Text.Raised
            styleColor: appStyle.shadowColor
            highlightColor: Qt.rgba(0.3,0.3,0.3,0.6)

            contents: [
                Form {
                    id: left
                    fontSize: appStyle.dataFontSize;
                    headerSize: appStyle.headerFontSize;
                    color: appStyle.textColor;

                    FormItem {
                        label: i18n("Humidity:")
                        value: conditions.humidity
                    }

                    FormItem {
                        label: i18n("Precipitation:")
                        value: conditions.precip
                    }

                    FormItem {
                        label: i18n("Feels like:")
                        value: conditions.feelsLike
                    }

                    FormItem {
                        label: i18n("Dew point:")
                        value: conditions.dewPoint
                    }

                    FormItem {
                        label: i18n("Pressure:")
                        value: conditions.pressure
                    }

                    FormItem {
                        label: i18n("Visibility:")
                        value: conditions.visibility
                    }

                    FormItem {
                        label: i18n("Cloud Cover:")
                        value: conditions.cloudCover
                    }

                    FormItem {
                        label: i18n("Wind:")
                        value: conditions.wind
                    }

                    FormItem {
                        label: i18n("Wind Gust:")
                        value: conditions.windGust
                    }
                }
            ]
        }
    }
}
