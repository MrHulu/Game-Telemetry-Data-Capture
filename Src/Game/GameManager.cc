#include "Game/GameManager.h"
#include "Game/GameRunMonitoringHelper.h"
#include "Game/Assetto Corsa/ACGame.h"
#include "Game/Assetto Corsa Competizione/ACCGame.h"
#include "Game/DiRT Rally 2.0/DirtRally2Game.h"
#include "Game/DiRT 4/Dirt4Game.h"

#include <algorithm>
#include <windows.h>
#include <tlhelp32.h>

class 创建进程快照失败{};


GameManager::GameManager(QObject *parent) : QObject(parent)
{   
    auto insertGame = [&](Game* game) {
        m_supportGames.insert(game->name(), game);
    };
    insertGame(new ACGame(this));
    insertGame(new ACCGame(this));
    insertGame(new DirtRally2Game(this));
    insertGame(new Dirt4Game(this));

    m_gameRunMonitoringHelper = new GameRunMonitoringHelper(m_supportGames, this);
    connect(m_gameRunMonitoringHelper, &GameRunMonitoringHelper::gameIsRunning, this, &GameManager::onGameIsRunning);
}

GameManager &GameManager::instance()
{
    static GameManager _instance;
    return _instance;
}

void GameManager::setRunningGame(Game *newRunningGame)
{
    if (m_runningGame == newRunningGame)
        return;
    if ( m_runningGame != nullptr) {
        m_runningGame->stopCapturer();
        m_runningGame->disconnect(nullptr, this, nullptr); //TODO: 不应该删除所有信号
    }

    m_runningGame = newRunningGame;
    emit runningGameChanged(m_runningGame);
    controlGameCapturer();
    if(m_runningGame == nullptr)
        return;
    connect(m_runningGame, &Game::isRunningChanged, this, &GameManager::controlGameCapturer);
}

Game *GameManager::findGame(const QString &name) const
{
    if (auto iter = m_supportGames.find(name);
        iter != m_supportGames.end())
    {
        return m_supportGames.value(name);
    }
    return nullptr;
}

void GameManager::onGameIsRunning(Game *game)
{
    if(game && m_runningGame == nullptr)
        setRunningGame(game);
    else if(game == nullptr)
        setRunningGame(nullptr);
}

void GameManager::controlGameCapturer()
{
    if(!m_runningGame)
        return;
    if(m_runningGame->isRunning())
        m_runningGame->startCapturer();
    else{
        m_runningGame->stopCapturer();
    }
}


