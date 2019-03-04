import QtQuick 2.0
import QtQuick.Controls 2.4

Action {
    property var command
    enabled: command.canExecute
    onTriggered: command.execute()
}
