import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import viewmodels 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Observable Property Sample")

    MainViewModel { id: vm }

    GridLayout {
        columns: 2
        anchors.centerIn: parent

        Label {
            text: vm.ivalue.value
            font.pixelSize: 16
        }
        SpinBox {
            Layout.fillWidth: true
            onValueChanged: vm.ivalue.value = value
        }

        Label {  }
        SpinBox {
            Layout.fillWidth: true
        }

        Label { }
        TextField { }
    }
}
