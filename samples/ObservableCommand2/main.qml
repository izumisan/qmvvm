import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import izm.qmvvm 1.0
import viewmodels 1.0

Window {
    visible: true
    width: 200
    height: 200
    title: qsTr("ObservableCommand sample")

    MainViewModel { id: vm }

    ColumnLayout {
        anchors.centerIn: parent

        Button {
            text: "sync: " + vm.value.value
            action: CommandAction { command: vm.command1 }
        }

        Button {
            text: "async: " + vm.value.value
            action: CommandAction { command: vm.command2 }
        }
    }
}
