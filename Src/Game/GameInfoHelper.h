#pragma once

#include <QObject>
#include <QMap>

class Game;

class GameInfoHelper : public QObject
{
    Q_OBJECT
    static constexpr auto GameInfoJsonFileName = "GameInfoFile.json";
public:
    GameInfoHelper(const QMap<QString, Game*>& games, QObject *parent = nullptr);

    void updateGameInfo();
    void checkAndRefreshLocalGameInfoFile();
    void writeGameInstallPathInfo(const QString& gameName, const QString& gameInstallPath);

private:
    QMap<QString, Game*> m_games;

    class GameInfoFileReadAndWrite;
    GameInfoFileReadAndWrite*   m_localAppDataGameInfoFile = nullptr;
    GameInfoFileReadAndWrite*   m_embeddedGameInfoFile = nullptr;

};

