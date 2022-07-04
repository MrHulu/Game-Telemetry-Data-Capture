#pragma once

#include <QObject>
#include <QMap>

class QTimer;
class Game;

class GameRunMonitoringHelper : public QObject
{
    Q_OBJECT
public:
    GameRunMonitoringHelper(const QMap<QString, Game *> &games, QObject *parent = nullptr);

signals:
    void gameIsRunning(const Game* game);

private:
    void monitoring();

private:
    QMap<QString, Game*>    m_games;
    QTimer* m_timer = nullptr;

};

