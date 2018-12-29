import QtQuick 2.0
import QtQuick.Controls 2.4

Action {
    property var command
    property bool isAsync: false

    enabled: command.canExecute
    onTriggered: {
        if ( !isAsync )
        {
            command.execute()
        }
        else
        {
            command.executeAsync()
        }
    }
}
