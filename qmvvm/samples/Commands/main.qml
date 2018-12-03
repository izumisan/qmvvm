import QtQuick 2.11
import QtQuick.Window 2.11


Window {
    visible: true
    width: 300
    height: 300
    title: qsTr("Commands")

    MainView {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
