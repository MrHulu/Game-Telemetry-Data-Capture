#include "Game/DiRT Rally 2.0/DirtRally2Game.h"


void DirtRally2Game::startCapturer()
{
    m_GameCapturer = new DirtRally2TelemetryDataCapturer;
    m_GameCapturer->setUdpInfoInCapturer(20777);
    m_GameCapturer->start();
    connect(m_GameCapturer, &QThread::finished, m_GameCapturer, &QObject::deleteLater);
    connect(m_GameCapturer, &QThread::finished, this, [&]{ m_GameCapturer = nullptr; });
}

void DirtRally2Game::stopCapturer()
{
    if(!m_GameCapturer)
        return;
    m_GameCapturer->setFlag(false);
}


DirtRally2Game::DirtRally2Game(QObject *parent) : GameWithUdp{parent}
{
    m_name = "DiRT Rally 2.0";
    m_captureMethod = NetWorkUDP;
    m_processName << "dirtrally2.exe";
}

DirtRally2Game::~DirtRally2Game()
{
    if(!m_GameCapturer)
        return;
    m_GameCapturer->setFlag(false);
}
