import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

import izm.qmvvm 1.0
import viewmodels 1.0

Item {

    MainViewModel { id: vm }

    ColumnLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: implicitWidth
        height: implicitHeight

        SpinBox {
            Layout.fillWidth: true

            value: vm.value
            onValueChanged: vm.value = value
        }

        RowLayout {
            width: implicitWidth
            spacing: 2
            ColumnLayout {
                spacing: 2
                Button {
                    text: "relay1"
                    action: Command { command: vm.relayCommand1 }
                }
                Button {
                    text: "async1"
                    action: Command { command: vm.asyncCommand1 }
                }
            }
            ColumnLayout {
                spacing: 2
                Button {
                    text: "relay2"
                    action: Command { command: vm.relayCommand2 }
                }
                Button {
                    text: "async2"
                    action: Command { command: vm.asyncCommand2 }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                id: label
                text: ""
                Layout.fillWidth: true

                Connections {
                    target: vm
                    onStarted: label.text = "waiting..."
                    onCompleted: label.text = ""
                }
            }
            Label {
                text: vm.message
            }
        }
    }
}
