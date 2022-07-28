import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import TelemetryDataCapture 1.0

TableView {
    id: view
    //implicitHeight: 400
    //implicitWidth: 400
    visible: true
    columnSpacing: 0
    rowSpacing: 1
    clip: true

    model: TelemetryDataTableModel { id: telemetryDataTableModel }

    delegate: Control {
        id: delegateControl
        hoverEnabled: true
        width: view.width / columns - 2 //TODO: 暂时不知道减去多少
        height: 42
        Rectangle {
            anchors.fill: parent
            color: {
                if(columns % 2) return "#B0BEC5"
                else return "#EEEEEE"
            }
        }
        Label {
            id: label
            text: model.display
            anchors.centerIn: parent
        }
    }// delegate
}
