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
    rowSpacing: 0
    clip: true

    model: TelemetryDataTableModel { id: telemetryDataTableModel }

    delegate: Control {
        id: delegateControl
        hoverEnabled: true
        width: label.implicitWidth
        height: label.implicitHeight === 0 ?  30 : label.implicitHeight
        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: Material.accent
        }
        Label {
            id: label
            text: model.display
            anchors.centerIn: parent
        }
    }// delegate
}
