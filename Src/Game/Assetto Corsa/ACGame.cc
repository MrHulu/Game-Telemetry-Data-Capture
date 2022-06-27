#include "Game/Assetto Corsa/ACGame.h"


void ACGame::startCapturer()
{
    m_GameCapturer = new ACTelemetryDataCapturer;
    m_GameCapturer->start();
    connect(m_GameCapturer, &QThread::finished, m_GameCapturer, &QObject::deleteLater);
    connect(m_GameCapturer, &QThread::finished, this, [&]{ m_GameCapturer = nullptr; });
}

void ACGame::stopCapturer()
{
    if(!m_GameCapturer)
        return;
    m_GameCapturer->setFlag(false);
}


ACGame::ACGame(QObject *parent) : Game{parent}
{
    m_processName << "acs.exe" << "AssettoCorsa.exe";
}

ACGame::~ACGame()
{
    if(!m_GameCapturer)
        return;
    m_GameCapturer->setFlag(false);
}
