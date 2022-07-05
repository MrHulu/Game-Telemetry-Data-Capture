#include "Game/GameInfoHelper.h"
#include "Game/Game.h"

GameInfoHelper::GameInfoHelper(const QMap<QString, Game*>& games, QObject *parent)
    :   QObject{parent},
        m_games{games}
{

}

void GameInfoHelper::updateGameInfo()
{

}
