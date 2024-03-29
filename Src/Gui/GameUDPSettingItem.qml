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
    enabled: game && !game.isRunning
    property GameWithUdp game
    readonly property bool error: !readPortTextField.acceptableInput || !writeAddressTextField.acceptableInput || !writeAddressTextField.acceptableInput

    ToolTip {
        id: toolTip
        y: -height - 5
    }
    Connections {
        target: game
        function onErrorOccurred(message) {
            toolTip.parent = title
            toolTip.y = -height
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
            font.weight: Font.Bold
            font.pixelSize: 16
        }
        Label {
            id: errorLabel
            visible: game && game.isRunning
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignLeft
            text: qsTranslate("","游戏运行中, 无法修改%1").arg(title.text)
            color: Material.color(Material.Red)
            font.pixelSize: 14
        }
        RowLayout {
            spacing: 8
            Label { text: qsTranslate("","UDP 接收端口") }
            TextField {
                id: readPortTextField
                Layout.alignment: Qt.AlignLeft
                //Layout.preferredHeight: 44
                Layout.preferredWidth: 68
                text: game ? game.readPort : null
                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                validator: IntValidator { bottom: 1025; top: 65535 }
                onAcceptableInputChanged: {
                    if(!acceptableInput && activeFocus) {
                        toolTip.parent = this
                        toolTip.y = -height
                        toolTip.show(qsTranslate("","非法的端口号"), -1)
                    }
                    else
                        if(toolTip.visible) toolTip.hide()
                }
                onActiveFocusChanged: {
                    if (!acceptableInput && !activeFocus) {
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
        }// UDP 接收端口
        RowLayout {
            spacing: 8
            Label { text: qsTranslate("","UDP 转发端口") }
            TextField {
                id: writePortTextField
                Layout.alignment: Qt.AlignLeft
                //Layout.preferredHeight: 44
                Layout.preferredWidth: 68
                text: game ? game.writePort : null
                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                validator: IntValidator { bottom: 1025; top: 65535 }
                onAcceptableInputChanged: {
                    if(!acceptableInput && activeFocus) {
                        toolTip.parent = this
                        toolTip.y = -height
                        toolTip.show(qsTranslate("","非法的端口号"), -1)
                    }
                    else
                        if(toolTip.visible) toolTip.hide()
                }
                onActiveFocusChanged: {
                    if (!acceptableInput && !activeFocus) {
                        text = Qt.binding(function() { return game ?  game.writePort.toFixed(0) : "HuluMan" })
                    }
                }
                onEditingFinished: {
                    if(game) {
                        game.writePort = parseInt(text)
                        text = Qt.binding(function() { return game.writePort.toFixed(0) })
                    }
                }
            }
        }// UDP 转发端口
        RowLayout {
            spacing: 8
            Label { text: qsTranslate("","UDP 转发地址") }
            TextField {
                id: writeAddressTextField
                Layout.alignment: Qt.AlignLeft
                //Layout.preferredHeight: 44
                Layout.preferredWidth: 68
                text: game ? game.writeAddress : null
                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                validator: RegExpValidator {
                    regExp: /((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}/
                }
                onAcceptableInputChanged: {
                    if(!acceptableInput && activeFocus) {
                        toolTip.parent = this
                        toolTip.y = -height
                        toolTip.show(qsTranslate("","非法的地址"), -1)
                    }
                    else
                        if(toolTip.visible) toolTip.hide()
                }
                onActiveFocusChanged: {
                    if (!acceptableInput && !activeFocus) {
                        text = Qt.binding(function() { return game ?  game.writeAddress : "HuluMan" })
                    }
                }
                onEditingFinished: {
                    if(game) {
                        game.writeAddress = text
                        text = Qt.binding(function() { return game.writeAddress })
                    }
                }
            }
        }// UDP 转发地址

    }// ColumnLayout

}// root
