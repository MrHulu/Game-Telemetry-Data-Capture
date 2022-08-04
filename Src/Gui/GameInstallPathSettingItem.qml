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

    property Game game
    property ToolTip toolTip

    ColumnLayout {
        id: layout
        width: parent.width
        Label {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignLeft
            text: qsTranslate("","游戏安装路径")
            //text: "%1 %2".arg(root.height).arg(layout.height)
        }
        RowLayout {
            spacing: 8
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 32
                border.width: 1
                border.color: Material.color(Material.Grey)
                radius: 4
                Label {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 16
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                    clip: true
                    text: game ? game.installPath : null
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onContainsMouseChanged:  {
                            if(game && game.installPath.length !== 0)  {
                                toolTip.parent = this
                                toolTip.text = game ? game.installPath : null
                                toolTip.y = -height - 5
                                toolTip.timeout = -1
                                toolTip.visible = containsMouse
                            }
                        }
                    }
                }// Label

            }// Rectangle
            Button {
                Layout.preferredWidth: 68
                Layout.preferredHeight: 44
                text: game && game.installPath.length !== 0 ? qsTranslate("", "修改") : qsTranslate("", "设置")
                onClicked: fileDialog.open()
            }
        }// RowLayout
    }// ColumnLayout

    FileDialog {
        id: fileDialog
        nameFilters: ["Executable files (*.exe)"]
        fileMode: FileDialog.OpenFile
        onAccepted: {
            if(game) {
                game.installPath = file
            }
        }
    }// fileDialog

}// root
