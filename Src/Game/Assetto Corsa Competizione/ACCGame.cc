#include "Game/Assetto Corsa Competizione/ACCGame.h"

void ACCGame::startCapturer()
{
    m_GameCapturer = new ACCTelemetryDataCapturer;
    m_GameCapturer->start();
    connect(m_GameCapturer, &QThread::finished, m_GameCapturer, &QObject::deleteLater);
    connect(m_GameCapturer, &QThread::finished, this, [&]{ m_GameCapturer = nullptr; });
}

void ACCGame::stopCapturer()
{
    if(!m_GameCapturer)
        return;
    m_GameCapturer->setFlag(false);
}


ACCGame::ACCGame(QObject *parent) : Game{parent}
{
    m_name = "Assetto Corsa Competizione";
    m_captureMethod = SharedMemory;
    m_processName << "acc.exe";
}

ACCGame::~ACCGame()
{
    if(!m_GameCapturer)
        return;
    m_GameCapturer->setFlag(false);
}
