#include "Game/DiRT 4/Dirt4Game.h"

void Dirt4Game::startCapturer()
{
    m_GameCapturer = new Dirt4TelemetryDataCapturer;
    m_GameCapturer->setUdpInfoInCapturer(20777);
    m_GameCapturer->start();
    connect(m_GameCapturer, &QThread::finished, m_GameCapturer, &QObject::deleteLater);
    connect(m_GameCapturer, &QThread::finished, this, [&]{ m_GameCapturer = nullptr; });
}

void Dirt4Game::stopCapturer()
{
    if(!m_GameCapturer)
        return;
    m_GameCapturer->setFlag(false);
}


Dirt4Game::Dirt4Game(QObject *parent) : GameWithUdp{parent}
{
    m_name = "DiRT 4";
    m_captureMethod = NetWorkUDP;
    m_processName << "dirt4.exe";
}

Dirt4Game::~Dirt4Game()
{
    if(!m_GameCapturer)
        return;
    m_GameCapturer->setFlag(false);
}
