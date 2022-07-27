import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import TelemetryDataCapture 1.0

ScrollView{
    id: control

    width: listView.width + 30


    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)
    ScrollBar.vertical.policy: ScrollBar.AsNeeded
    ScrollBar.vertical.width: 8
    ScrollBar.vertical.x: control.width - ScrollBar.vertical.width * 2

    Flickable {
        clip: true
        topMargin: 0
        contentHeight: listView.height //- gameItem.Layout.bottomMargin
        contentWidth: listView.width

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
