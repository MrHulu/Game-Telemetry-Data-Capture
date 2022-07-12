#include "Game/GameInfoHelper.h"
#include "Game/GameInfoHelperFileAnalysis.h"
#include "Game/Game.h"

namespace Environment {
    extern QString applicationInfoPath();
}// Envirnment

namespace Utils {
    extern int versionCompare(const QString &lhs, const QString &rhs);
}// Utils


GameInfoHelper::GameInfoHelper(const QMap<QString, Game*>& games, QObject *parent)
    :   QObject{parent},
        m_games{games}
{
    auto localGameInfoFilePath = QString("%1/%2").arg(Environment::applicationInfoPath(), GameInfoJsonFileName);
    auto embeddedGameInfoFilePath = QString("://Information/GameInfo.json");
    m_localAppDataGameInfoFile = new GameInfoFileReadAndWrite(localGameInfoFilePath, *this);
    m_embeddedGameInfoFile = new GameInfoFileReadAndWrite(embeddedGameInfoFilePath, *this);
}

void GameInfoHelper::updateGameInfo()
{

}

void GameInfoHelper::checkAndRefreshLocalGameInfoFile()
{
    // 优先级： 版本 > 修改时间
    auto localVer =  m_localAppDataGameInfoFile->fileVersion();
    auto embeddedVer = m_embeddedGameInfoFile->fileVersion();
    auto ret = Utils::versionCompare(localVer, embeddedVer);
    if(ret == -1) {
        m_embeddedGameInfoFile->creatGameInfoFile();
        m_localAppDataGameInfoFile->readGameInfoFile();
        return;
    }
    else if(ret == 0) {

        // 比较文件修改时间
        if(m_localAppDataGameInfoFile->fileChangeTime() < m_embeddedGameInfoFile->fileChangeTime()) {
            m_embeddedGameInfoFile->creatGameInfoFile();
            m_localAppDataGameInfoFile->readGameInfoFile();
        }
    }
}

void GameInfoHelper::writeGameInstallPathInfo(const QString &gameName, const QString &gameInstallPath)
{

}
