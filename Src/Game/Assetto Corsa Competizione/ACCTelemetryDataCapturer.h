#pragma once

#include "Game/Capturer.h"
#include "Game/Assetto Corsa Competizione/SharedMemoryPacket.h"



class SMGraphicsElement;
class SMPysicsElement;
class SMStaticElement;

class ACCTelemetryDataCapturer : public Capturer
{
public:
    explicit ACCTelemetryDataCapturer(QObject *parent = nullptr);
    void setFlag(bool flag) override;

protected:
    void run() override;

public slots:

signals:

private:
    void captureAndCompare();
    std::unique_ptr<SMGraphicsElement> m_graphics;
    std::unique_ptr<SMPysicsElement> m_physics;
    std::unique_ptr<SMStaticElement> m_static;
    bool m_flag = true;
};


inline void ACCTelemetryDataCapturer::setFlag(bool flag) { m_flag = flag; }
