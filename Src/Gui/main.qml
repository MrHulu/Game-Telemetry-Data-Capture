import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: root
    width: 1024
    height: 820
    visible: true

//    background: Rectangle {
//        gradient: Gradient {
//            GradientStop { position: 0.0; color: "#D1FFFFFF" }
//            GradientStop { position: 1.0; color: "#FFF2F6FA" }
//        }
//    }

    Button {
        text:  "text"
        highlighted: true
        anchors.centerIn: parent
    }
    Item {
        id: view
        anchors.left: root.contentItem.left
        anchors.top: root.contentItem.top
        anchors.bottom: root.contentItem.bottom
        anchors.right: root.contentItem.right
        anchors.leftMargin: 30
        anchors.rightMargin: 30

        GameList {
            height: view.height
            anchors.right: view.right
        }
    }// view
}
