import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item {
    property alias _button: button
    property alias _label: label

    width: column.width
    height: column.height

    ColumnLayout {
        id: column
        width: implicitWidth
        height: implicitHeight

        Button {
            id: button
        }
        Label {
            id: label
        }
    }
}
