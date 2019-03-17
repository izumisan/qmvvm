import QtQuick 2.0
import QtQuick.Controls 2.5

Action {
    /**
     * VMが提供するコマンド
     * @type {CommandBase}
     */
    property var command
    enabled: command.canExecute
    onTriggered: command.execute()
}
