import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1
import QtQuick.Controls.Material 2.15

ApplicationWindow {
    id: root
    width: 1024
    height: 820
    visible: true
    Material.theme: Material.System
    Material.accent: Material.Teal

    background: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#D1FFFFFF" }
            GradientStop { position: 1.0; color: "#FFF2F6FA" }
        }
    }
    GameItem {}
}
