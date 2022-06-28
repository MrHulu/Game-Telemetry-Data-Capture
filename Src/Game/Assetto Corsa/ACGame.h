#pragma once

#include "Game/Game.h"
#include "Game/Assetto Corsa/ACTelemetryDataCapturer.h"

class ACGame : public Game
{
public:
    explicit ACGame(QObject *parent = nullptr);
    ~ACGame() override;

    void startCapturer() override;
    void stopCapturer() override;

private:
    ACTelemetryDataCapturer *m_GameCapturer = nullptr;
};




