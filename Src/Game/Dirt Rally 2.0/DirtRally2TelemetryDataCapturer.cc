#include "Game/Dirt Rally 2.0/DirtRally2TelemetryDataCapturer.h"
#include <QtAlgorithms>


DirtRally2TelemetryDataCapturer::DirtRally2TelemetryDataCapturer(QObject *parent)
    : CapturerWithUdp{parent}
{

}


void DirtRally2TelemetryDataCapturer::run()
try{

    qDebug()<<"start Dirt Rally 2.0 capture!";

    while (m_flag)
    {
        captureAndCompare();
        //QThread::msleep(10);
    }

    TelemetryDataBuffer::Instance().remove();
    lastTelemetryData.remove();

    m_socket->deleteLater();
}
catch(const char *msg){
    qDebug()<<"throw: "<<msg;
    TelemetryDataBuffer::Instance().remove();
    lastTelemetryData.remove();
    m_socket->deleteLater();
    return;
}

void DirtRally2TelemetryDataCapturer::capturingAndForwarding()
{
    auto rawData = capturing();
    if(rawData.isEmpty()) return;
    auto data = *reinterpret_cast<Dirt2TelemetryData*>(rawData.data());
    m_data.push(data);
    forwarding(rawData);
}

void DirtRally2TelemetryDataCapturer::captureAndCompare()
{
    QMap<QString,QVariant> changeData;
    const auto& lastData = this->lastTelemetryData.get();

    auto checkAndInsert = [&](auto rawDataProperty, const QString& subjectPath) {
        if (auto iter = lastData.find(subjectPath);
                iter == lastData.end() || *iter != rawDataProperty)
            changeData.insert(subjectPath, rawDataProperty);
    };

    capturingAndForwarding();
    if (m_data.empty())
        return;
    Dirt2TelemetryData packet = m_data.front();
    m_data.pop();

    checkAndInsert(packet.Speed_MS * 0.62 * 3.6, "SpeedMph");
    checkAndInsert(packet.Speed_MS * 3.6, "SpeedKmh");
    checkAndInsert(packet.Speed_MS, "SpeedMs");
    checkAndInsert(packet.EngineRate * 10, "Rpm");
    checkAndInsert(packet.Max_rpm * 10, "MaxRpm");
    checkAndInsert(packet.Gear, "Gear");
    checkAndInsert(packet.laps_completed, "CurrentLap");
    checkAndInsert(packet.Car_position, "CurrentPos");
    checkAndInsert(packet.Last_lap_time, "LastLapTime");
    checkAndInsert(packet.Wheels_pressure_bl,"TyrePressureRearLeft");
    checkAndInsert(packet.Wheels_pressure_br,"TyrePressureRearRight");
    checkAndInsert(packet.Wheels_pressure_fl,"TyrePressureFrontLeft");
    checkAndInsert(packet.Wheels_pressure_fr,"TyrePressureFrontRight");
    if(packet.Fuel_capacity > 0.0f) checkAndInsert(floor(packet.Fuel_in_tank / packet.Fuel_capacity * 100) ,"FuelRemainder");
    checkAndInsert(packet.ABS,"ABSActive");
    checkAndInsert(packet.Throttle,"Throttle");
    checkAndInsert(packet.Brake,"Brake");
    checkAndInsert(packet.Sector,"SectorIndex");
    checkAndInsert(packet.Total_laps,"CurrentLapCount");

    Capturer::lastTelemetryData.update(changeData);
}
