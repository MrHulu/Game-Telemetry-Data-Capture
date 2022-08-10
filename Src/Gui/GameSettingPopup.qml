import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.platform 1.1
import QtGraphicalEffects 1.0
import TelemetryDataCapture 1.0

Popup {
    id: popup
//    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
//                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)
    implicitWidth: 560
//    implicitHeight: 268
    parent: ApplicationWindow.window ? ApplicationWindow.window.contentItem : null
    x: parent ? Math.round((parent.width - width) / 2) : 0
    y: parent ? Math.round((parent.height - height) / 2) : 0
    visible: false
    modal: true
    clip: false
    closePolicy: Popup.NoAutoClose
    leftPadding: 48
    rightPadding: 48
    topPadding: 24
    bottomMargin: 24

    property Game game
    property GameWithUdp udpGame: game && (game.captureMethod === Game.NetWorkUDP || game.captureMethod === Game.UDPAndSM) ?
                                      game : null
    ToolTip {
        id: toolTip
        y: -height - 5
    }
    contentItem: Item {
        ColumnLayout {
            width: parent.width
            spacing: 10
            Label {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                text: qsTranslate("", "%1设置").arg(game ? game.name : qsTranslate("", "游戏"))
            }
            DividingLine {}
            GameInstallPathSettingItem {
                game: popup.game
                toolTip: toolTip
            }
            DividingLine {}
            GameUDPSettingItem {
                id: gameUDPSettingItem
                visible: popup.udpGame
                game: popup.udpGame
            }
            DividingLine {}
            GameTelemetryConfigTutorialItem { game: popup.game }
            DividingLine {}
            RowLayout {
                Button {
                    Layout.preferredHeight: 44
                    Layout.preferredWidth: 100
                    Layout.alignment: Qt.AlignRight
                    highlighted: true
                    font.weight: Font.Bold
                    font.pixelSize: 16
                    text: qsTranslate("", "确定")
                    enabled: !gameUDPSettingItem.error
                    onClicked: popup.close()
                }
                Item { Layout.fillWidth: true }
                Button {
                    //visible: false
                    Layout.preferredHeight: 44
                    Layout.preferredWidth: 100
                    Layout.alignment: Qt.AlignLeft
                    font.weight: Font.Bold
                    font.pixelSize: 16
                    text: qsTranslate("","取消")
                    onClicked: popup.close()
                }
            }
        }
    }// contentItem

    background: Item {
        Rectangle {
            id: blank
            anchors.fill: parent
            color: "#FFFFFFFF"
            radius: 4
        }
        DropShadow {
            anchors.fill: parent
            source: blank
            verticalOffset: 8
            horizontalOffset: 8
            radius: 28
            samples: 20
            color: "#24565759"
        }
    }// background
}
