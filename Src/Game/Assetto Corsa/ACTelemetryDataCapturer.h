#pragma once

#include "Game/Capturer.h"
#include "Game/Assetto Corsa/SharedMemoryPacket.h"

#include <QThread>


class SMGraphicsElement;
class SMPysicsElement;
class SMStaticElement;

class ACTelemetryDataCapturer : public Capturer
{
public:
    explicit ACTelemetryDataCapturer(QObject *parent = nullptr);
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


inline void ACTelemetryDataCapturer::setFlag(bool flag) { m_flag = flag; }
