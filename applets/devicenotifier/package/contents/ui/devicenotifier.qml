/*
 *   Copyright 2011 Viranch Mehta <viranch.mehta@gmail.com>
 *   Copyright 2012 Jacopo De Simoi <wilderkde@gmail.com>
 *   Copyright 2014 David Edmundson <davidedmundson@kde.org>
 *
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.extras 2.0 as PlasmaExtras

Item {
    id: devicenotifier
    property string devicesType: {
        if (plasmoid.configuration.allDevices) {
            return "all"
        } else if (plasmoid.configuration.removableDevices) {
            return "removable"
        } else {
            return "nonRemovable"
        }
    }
    property string expandedDevice
    property string popupIcon: "device-notifier"

    property bool itemClicked: false
    property int currentIndex: -1

    // QTBUG-50380: As soon as the item gets removed from the model, all of ListView's
    // properties (count, contentHeight) pretend the delegate doesn't exist anymore
    // causing our "No devices" heading to overlap with the remaining device
    property int pendingDelegateRemoval: 0

    Plasmoid.switchWidth: units.gridUnit * 10
    Plasmoid.switchHeight: units.gridUnit * 10

    Plasmoid.toolTipMainText: filterModel.count > 0 && filterModel.get(0) ? i18n("Most Recent Device") : i18n("No Devices Available")
    Plasmoid.toolTipSubText: {
        if (filterModel.count > 0) {
            var data = filterModel.get(0)
            if (data && data.Description) {
                return data.Description
            }
        }
        return ""
    }
    Plasmoid.icon: {
        if (filterModel.count > 0) {
            var data = filterModel.get(0)
            if (data && data.Icon) {
                return data.Icon
            }
        }
        return "device-notifier"
    }

    Plasmoid.status: (filterModel.count > 0 || pendingDelegateRemoval > 0) ? PlasmaCore.Types.ActiveStatus : PlasmaCore.Types.PassiveStatus

    PlasmaCore.DataSource {
        id: hpSource
        engine: "hotplug"
        connectedSources: sources
        interval: 0

        onSourceAdded: {
            disconnectSource(source);
            connectSource(source);
        }
        onSourceRemoved: {
            disconnectSource(source);
        }
    }

    Plasmoid.compactRepresentation: PlasmaCore.IconItem {
        source: devicenotifier.popupIcon
        width: units.iconSizes.medium;
        height: units.iconSizes.medium;
        MouseArea {
            anchors.fill: parent
            onClicked: plasmoid.expanded = !plasmoid.expanded
        }
    }
    Plasmoid.fullRepresentation: FullRepresentation {}

    PlasmaCore.DataSource {
        id: sdSource
        engine: "soliddevice"
        connectedSources: hpSource.sources
        interval: plasmoid.expanded ? 5000 : 0
        property string last
        onSourceAdded: {
            disconnectSource(source);
            connectSource(source);
            last = source;
            processLastDevice(true);
        }

        onSourceRemoved: {
            if (expandedDevice == source) {
                expandedDevice = "";
            }
            disconnectSource(source);
        }

        onDataChanged: {
            processLastDevice(true);
        }

        onNewData: {
            last = sourceName;
            processLastDevice(false);
        }

        function processLastDevice(expand) {
            if (last != "") {
                if (devicesType == "all" ||
                    (devicesType == "removable" && data[last] && data[last]["Removable"] == true) ||
                    (devicesType == "nonRemovable" && data[last] && data[last]["Removable"] == false)) {
                    if (expand && hpSource.data[last]["added"]) {
                        expandDevice(last)
                    }
                    last = "";
                }
            }
        }
    }

    PlasmaCore.SortFilterModel {
        id: filterModel
        sourceModel: PlasmaCore.DataModel {
            dataSource: sdSource
        }
        filterRole: "Removable"
        filterRegExp: {
            if (devicesType === "removable") {
                return "true"
            } else if (devicesType === "nonRemovable") {
                return "false"
            } else {
                return ""
            }
        }
        sortRole: "Timestamp"
        sortOrder: Qt.DescendingOrder
    }

    PlasmaCore.DataSource {
        id: statusSource
        engine: "devicenotifications"
        property string last
        property string lastUdi
        onSourceAdded: {
            last = source;
            disconnectSource(source);
            connectSource(source);
        }
        onSourceRemoved: disconnectSource(source)
        onDataChanged: {
            if (last) {
                lastUdi = data[last].udi
                plasmoid.expanded = true
            }
        }

        function clearMessage() {
            last = ""
            lastUdi = ""
        }
    }

    Component.onCompleted: {
        if (sdSource.connectedSources.count == 0) {
            Plasmoid.status = PlasmaCore.Types.PassiveStatus;
        }
    }

    Plasmoid.onExpandedChanged: {
        popupEventSlot(plasmoid.expanded);
    }

    function popupEventSlot(popped) {
        if (!popped) {
            // reset the property that lets us remember if an item was clicked
            // (versus only hovered) for autohide purposes
            devicenotifier.itemClicked = true;
            expandedDevice = "";
            devicenotifier.currentIndex = -1;
        }
    }

    function expandDevice(udi) {
        if (hpSource.data[udi]["actions"].length > 1) {
            expandedDevice = udi
        }

        // reset the property that lets us remember if an item was clicked
        // (versus only hovered) for autohide purposes
        devicenotifier.itemClicked = false;

        devicenotifier.popupIcon = "preferences-desktop-notification";
        //plasmoid.expanded = true;
        expandTimer.restart();
        popupIconTimer.restart()
    }

    function isMounted(udi) {
        var types = sdSource.data[udi]["Device Types"];
        if (types.indexOf("Storage Access") >= 0) {
            return sdSource.data[udi]["Accessible"];
        }

        return (types.indexOf("Storage Volume") >= 0 && types.indexOf("OpticalDisc") >= 0)
    }

    Timer {
        id: popupIconTimer
        interval: 3000
        onTriggered: devicenotifier.popupIcon  = "device-notifier";
    }

    Timer {
        id: expandTimer
        interval: 250
        onTriggered: {
            if (plasmoid.configuration.popupOnNewDevice) { // Bug 351592
                plasmoid.expanded = true;
            }
        }
    }

}
