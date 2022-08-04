import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.platform 1.1
import TelemetryDataCapture 1.0

Item {
    id: root
    Layout.fillWidth: true
    Layout.preferredHeight: layout.height // 自适应高度
    property GameWithUdp game
    property ToolTip toolTip

    Connections {
        target: game
        function onErrorOccurred(message) {
            toolTip.parent = title
            toolTip.y = -height - 5
            toolTip.show(message, 2000)
        }
    }
    ColumnLayout {
        id: layout
        width: parent.width
        Label {
            id: title
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignLeft
            text: qsTranslate("","UDP 配置")
        }
        Label {
            id: errorLabel
            visible: game && game.isRunning
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignLeft
            text: qsTranslate("","游戏运行中, 无法修改%1").arg(title.text)
        }
        RowLayout {
            spacing: 8
            Label { text: qsTranslate("","UDP 接收端口") }
            TextField {
                id: textField
                Layout.alignment: Qt.AlignLeft
                Layout.preferredHeight: 44
                Layout.preferredWidth: 68
                enabled: game && !game.isRunning
                text: game ? game.readPort : null
                validator: IntValidator { bottom: 1025; top: 65535 }
                onActiveFocusChanged: {
                    if (!acceptableInput && !activeFocus) {
                        toolTip.parent = this
                        toolTip.y = -height - 5
                        toolTip.show(qsTranslate("","非法的端口号"), 2000)
                        text = Qt.binding(function() { return game ?  game.readPort.toFixed(0) : "HuluMan" })
                    }
                }
                onEditingFinished: {
                    if(game) {
                        game.readPort = parseInt(text)
                        text = Qt.binding(function() { return game.readPort.toFixed(0) })
                    }
                }
            }
        }// RowLayout

    }// ColumnLayout

}// root
