#pragma once

#include "Game/Game.h"
#include "Game/Assetto Corsa Competizione/ACCTelemetryDataCapturer.h"

class ACCGame : public Game
{
public:
    explicit ACCGame(QObject *parent = nullptr);
    ~ACCGame() override;

    void startCapturer() override;
    void stopCapturer() override;

private:
    ACCTelemetryDataCapturer *m_GameCapturer = nullptr;
};




