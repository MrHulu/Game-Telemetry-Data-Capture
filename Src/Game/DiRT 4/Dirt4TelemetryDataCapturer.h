#pragma once
#include "Game/CapturerWithUdp.h"
#include "Game/DiRT 4/UdpPacket.h"

#include <queue>

class Dirt4TelemetryDataCapturer : public CapturerWithUdp
{
public:
    Dirt4TelemetryDataCapturer(QObject *parent = nullptr);

    void setFlag(bool flag) override;

protected:
    void run() override;

private:
    void capturingAndForwarding();

private:
    void captureAndCompare();
    bool m_flag = true;
    std::queue<Dirt4TelemetryData> m_data;
};

inline void Dirt4TelemetryDataCapturer::setFlag(bool flag) { m_flag = flag; }
