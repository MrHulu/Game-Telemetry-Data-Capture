#pragma once

#include <QObject>
#include <QMap>

class Game;

class GameInfoHelper : public QObject
{
    Q_OBJECT
public:
    GameInfoHelper(const QMap<QString, Game*>& games, QObject *parent = nullptr);

    void updateGameInfo();

private:
    QMap<QString, Game*> m_games;

    class GameInfoFileAnalysis;
    GameInfoFileAnalysis*   m_gameInfoFileAnalysis = nullptr;

};

