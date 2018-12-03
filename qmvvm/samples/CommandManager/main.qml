import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import viewmodels 1.0

Window {
    id: window
    visible: true
    width: 200
    height: 200
    title: qsTr("CommandManager")

    MainViewModel { id: vm }

    ColumnLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        SpinBox {
            onValueChanged: vm.value = value
        }

        Button {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            text: qsTr("Relay Command")

            enabled: vm.relayCommand.canExecute
            onClicked: vm.relayCommand.execute()
        }

        Label {
            text: "click: " + vm.count

            Layout.alignment: Qt.AlignBottom | Qt.AlignRight
        }
    }
}
