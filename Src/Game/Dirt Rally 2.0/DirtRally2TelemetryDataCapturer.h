#pragma once
#include "Game/CapturerWithUdp.h"
#include "Game/Dirt Rally 2.0/UdpPacket.h"

#include <queue>

class DirtRally2TelemetryDataCapturer : public CapturerWithUdp
{
public:
    DirtRally2TelemetryDataCapturer(QObject *parent = nullptr);

    void setFlag(bool flag) override;

protected:
    void run() override;

private:
    void capturingAndForwarding();

private:
    void captureAndCompare();
    bool m_flag = true;
    std::queue<Dirt2TelemetryData> m_data;
};

inline void DirtRally2TelemetryDataCapturer::setFlag(bool flag) { m_flag = flag; }
