import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import TelemetryDataCapture 1.0

Control {
    id: control
    padding: 0
    hoverEnabled: true
    Layout.preferredHeight: 140
    Layout.preferredWidth: 210
    implicitWidth: 210
    implicitHeight: 140

    visible: game
    property Game game
    readonly property bool isUdpGame: game ? (game.captureMethod === game.UDPAndSM || game.captureMethod === game.NetWorkUDP) : false
    readonly property GameWithUdp gameUdp: game &&  isUdpGame ? game : null
    readonly property string gameName: game ? game.name : null

    ToolTip {

    }

    OpacityMask {
        anchors.fill: control
        source: Image {
            width: control.width
            height: control.height
            source: "images/%1.jpg".arg(gameName)
            fillMode: Image.Stretch
            smooth: true
            mipmap: true
        }
        maskSource: Rectangle {
            width: control.width
            height: control.height
            radius: 4
        }
    }// OpacityMask

    Rectangle {
        id: mask
        anchors.fill: parent
        visible: control.hovered
        radius: 4
        opacity: 0.65
        color: "#FF000000"
    }

    ColumnLayout {
        visible: control.hovered
        anchors.centerIn: control
        Button {
            highlighted: true
            Layout.preferredHeight: 44
            Layout.preferredWidth: implicitWidth
            id: gameStartButton
            text: qsTranslate("", "启动")
        }
        Button {
            highlighted: true
            id: settingButton
            Layout.preferredHeight: 44
            Layout.preferredWidth: implicitWidth
            text: qsTranslate("", "设置")
        }
    }// ColumnLayout

}// Control
