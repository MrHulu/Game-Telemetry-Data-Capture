#include "Game/GameInfoHelper.h"
#include "Game/Game.h"

namespace Environment {
    extern QString applicationInfoPath();
}// Envirnment


GameInfoHelper::GameInfoHelper(const QMap<QString, Game*>& games, QObject *parent)
    :   QObject{parent},
        m_games{games}
{

}

void GameInfoHelper::updateGameInfo()
{

}
