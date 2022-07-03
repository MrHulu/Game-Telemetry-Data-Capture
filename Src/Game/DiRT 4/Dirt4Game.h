#pragma once
#include "Game/GameWithUdp.h"
#include "Game/DiRT 4/Dirt4TelemetryDataCapturer.h"

class Dirt4Game : public GameWithUdp
{
public:
    explicit Dirt4Game(QObject *parent = nullptr);
    ~Dirt4Game() override;

    void startCapturer() override;
    void stopCapturer() override;

private:
    Dirt4TelemetryDataCapturer *m_GameCapturer = nullptr;
};


