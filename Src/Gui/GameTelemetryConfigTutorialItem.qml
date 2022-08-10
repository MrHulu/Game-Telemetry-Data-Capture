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
    property Game game

    RowLayout {
        id: layout
        spacing: 1
        width: root.width
        Label {
            id: label
            font.pixelSize: 16
            font.weight: Font.Bold
            text: qsTranslate("","如何启用%1游戏遥测功能").arg(game ? game.name : null)
            color: mouseArea.containsMouse ? "#666666" : "#333333"
        }
        Image {
            id: image
            fillMode: Image.PreserveAspectFit
            width: 20
            height: 20
            smooth: true
            sourceSize { height: 14; width: 14 }
            source: mouseArea.containsMouse ? "icons/help_hovered.svg" : "icons/help_normal.svg"
        }
        Item { Layout.fillWidth: true }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: layout
        hoverEnabled: true
        cursorShape: Qt.WhatsThisCursor
        onClicked: {}
    }// MouseArea
}
