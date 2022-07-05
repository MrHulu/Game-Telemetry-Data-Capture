#pragma once

#include "Game/GameInfoHelper.h"

#include <QObject>
#include <QDateTime>

class GameInfoHelper::GameInfoFileAnalysis : public QObject
{
    Q_OBJECT
    static constexpr auto GameInfoFileName = "GameInfo.json";
public:
    GameInfoFileAnalysis(GameInfoHelper& helper);

    void analyze();

private:
    QString gameInfoFilePath();


private:
    GameInfoHelper& gameInfoHelper;

    QByteArray      m_fileData;
    QString         m_fileVersion;
    QDateTime       m_fileChangeTime;
};

