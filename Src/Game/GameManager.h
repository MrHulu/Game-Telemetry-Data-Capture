#pragma once

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QMap>

class Game;
class GameRunMonitoringHelper;

class GameManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Game* runningGame READ runningGame WRITE setRunningGame NOTIFY runningGameChanged)
    Q_PROPERTY(QMap<QString,Game*> supportGames READ supportGames CONSTANT)

public:
    explicit GameManager(QObject *parent = nullptr);
    static GameManager& instance();

    Game *runningGame() const;
    void setRunningGame(Game *newRunningGame);
    const QMap<QString, Game *> &supportGames() const;
    Q_INVOKABLE Game* findGame(const QString& name) const;

signals:
    void runningGameChanged(Game* runningGame);

private slots:
    void onGameIsRunning(Game *game);
    void controlGameCapturer();

private:
    GameRunMonitoringHelper*    m_gameRunMonitoringHelper = nullptr;
    Game *m_runningGame = nullptr;
    QMap<QString, Game *> m_supportGames;
};

inline Game *GameManager::runningGame() const { return m_runningGame; }
inline const QMap<QString, Game *> &GameManager::supportGames() const { return m_supportGames; }
