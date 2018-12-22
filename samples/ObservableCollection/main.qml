import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import viewmodels 1.0

Window {
    visible: true
    width: 400
    height: 400
    title: qsTr("ObservableCollection")

    MainViewModel { id: vm }

    ListView {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -50
        anchors.verticalCenter: parent.verticalCenter
        width: contentWidth
        height: contentHeight

        model: vm.collection

        delegate: Button {
            text: model.value
            onClicked: model.value += 1
        }
    }
}
