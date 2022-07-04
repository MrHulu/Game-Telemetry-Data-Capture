#include "Game/GameRunMonitoringHelper.h"
#include "Game/Game.h"

#include <windows.h>
#include <tlhelp32.h>

#include <QTimer>
#include <QDebug>

GameRunMonitoringHelper::GameRunMonitoringHelper(const QMap<QString, Game*>& games, QObject *parent)
    :   QObject{parent},
        m_games{games},
        m_timer{new QTimer(this)}
{
    m_timer->setInterval(1000);
    m_timer->start();
    connect(m_timer, &QTimer::timeout, this, &GameRunMonitoringHelper::monitoring);
}

void GameRunMonitoringHelper::monitoring()
{
    auto processSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (processSnap == INVALID_HANDLE_VALUE) {
        qWarning()<<"CreateToolhelp32Snapshot fail!";
        return;
    }

    // 获取所有进程
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    bool hasNext = ::Process32First(processSnap, &pe32);
    QSet<QString> processNames;
    while (hasNext)
    {
        QString processName = QString::fromUtf8(pe32.szExeFile);
        processNames.insert(processName);
        hasNext = ::Process32Next(processSnap, &pe32);
    }
    ::CloseHandle(processSnap);

    //qDebug()<<"进程"<<":"<<processNames;

    // 检测游戏进程是否存在
    auto noGameRunnigCount = 0;
    for(auto i = m_games.constBegin();i != m_games.constEnd();++i)
    {
        auto game = i.value();
        bool isRunning = processNames.intersects(game->processNames());
        game->setIsRunning(isRunning);
        if(isRunning)
            emit gameIsRunning(game);
        else
            noGameRunnigCount++;
    }

    if(noGameRunnigCount == m_games.size())
        emit gameIsRunning(nullptr);
}
