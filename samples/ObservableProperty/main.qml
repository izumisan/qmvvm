import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import viewmodels 1.0

Window {
    visible: true
    width: 400
    height: 350
    title: qsTr("Observable Property Sample")

    MainViewModel { id: vm }

    GridLayout {
        columns: 2
        anchors.centerIn: parent

        Label {
            text: vm.ivalue.value
            font.pixelSize: 16
            Layout.minimumWidth: 50
        }
        SpinBox {
            value: vm.ivalue.value
            Layout.fillWidth: true

            onValueChanged: vm.ivalue.value = value
        }


        Label {
            text: vm.fooName.value
            font.pixelSize: 16
        }
        TextField {
            text: vm.fooName.value

            onTextEdited: vm.fooName.value = text
        }

        Label {
            text: vm.fooValue.value
            font.pixelSize: 16
        }
        SpinBox {
            value: vm.fooValue.value
            Layout.fillWidth: true

            onValueChanged: vm.fooValue.value = value
        }
    }

    Button {
        text: "print foo"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 20
        anchors.rightMargin: 20

        onClicked: vm.printFooValue()
    }
}
