#include "Game/GameInfoHelperFileAnalysis.h"

namespace Envirnment {
    extern QString applicationInfoPath();
}// Envirnment

GameInfoHelper::GameInfoFileAnalysis::GameInfoFileAnalysis(GameInfoHelper& helper)
    :   QObject{&helper},
        gameInfoHelper{helper}
{

}

void GameInfoHelper::GameInfoFileAnalysis::analyze()
{

}

QString GameInfoHelper::GameInfoFileAnalysis::gameInfoFilePath()
{
    return QString("%1/%2").arg(applicationInfoPath()).arg(GameInfoFileName);
}
