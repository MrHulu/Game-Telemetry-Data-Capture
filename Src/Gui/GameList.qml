import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import TelemetryDataCapture 1.0


ScrollView{
    id: control
    property alias verScrollbar: verScrollbar
    property alias horScrollbar: horScrollbar

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)
    ScrollBar.vertical: ScrollBar {
        id: verScrollbar
        parent: control
        x: control.mirrored ? 0 : control.width - width
        y: control.topPadding
        height: control.availableHeight * 2
        active: control.ScrollBar.vertical.active
    }
    ScrollBar.horizontal: ScrollBar {
        id: horScrollbar
        parent: control
        x: control.leftPadding
        y: control.height - height
        width: control.availableWidth * 2
        active: control.ScrollBar.horizontal.active
        policy: ScrollBar.AlwaysOff
    }

    Flickable {
        clip: true
        topMargin: 0
        contentHeight: listView.height //- gameItem.Layout.bottomMargin
        contentWidth: listView.width// + leftMargin + rightMargin
        //ScrollBar.vertical.x: width - 10

        ListView{
           id: listView
           spacing: 12
           Component.onCompleted: {
               var games = GameManager.supportGames
               for(var i=0; i<games.length; i++) {
                   listModel.append({"gameName": games[i] })
               }
           }
           currentIndex: 0;
           model: ListModel {
               id:listModel
           }// listModel

           delegate: GameItem {
               game: GameManager.findGame(model.gameName)
           }// GameItem

           height: count * 152 -12
           width: currentItem ? currentItem.width : 300
        }
    }//Flickable
}
