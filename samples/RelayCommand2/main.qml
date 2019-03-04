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
    title: qsTr("ViewModel sample")

    MainViewModel { id: vm }

    ColumnLayout {
        anchors.centerIn: parent

        SpinBox {
            onValueChanged: vm.value.value = value
        }

        Button {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            text: "3の倍数で押せるボタン"

            action: CommandAction { command: vm.command }
        }
    }
}
