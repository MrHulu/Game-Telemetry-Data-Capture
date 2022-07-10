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

private:
    QMap<QString, Game*> m_games;

    class GameInfoFileReadAndWrite;
    GameInfoFileReadAndWrite*   m_gameInfoFileAnalysis = nullptr;

};

