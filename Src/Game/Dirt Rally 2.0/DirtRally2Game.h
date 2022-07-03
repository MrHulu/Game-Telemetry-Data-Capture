#pragma once
#include "Game/GameWithUdp.h"
#include "Game/Dirt Rally 2.0/DirtRally2TelemetryDataCapturer.h"

class DirtRally2Game : public GameWithUdp
{
public:
    explicit DirtRally2Game(QObject *parent = nullptr);
    ~DirtRally2Game() override;

    void startCapturer() override;
    void stopCapturer() override;

private:
    DirtRally2TelemetryDataCapturer *m_GameCapturer = nullptr;
};


