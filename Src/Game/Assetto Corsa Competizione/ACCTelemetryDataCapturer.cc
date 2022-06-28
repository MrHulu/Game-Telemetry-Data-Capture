#include "Game/Assetto Corsa Competizione/ACCTelemetryDataCapturer.h"

#include <Windows.h>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include <QThread>

#include <windows.h>

using namespace ACC;

ACCTelemetryDataCapturer::ACCTelemetryDataCapturer(QObject *parent)
{

}

class SMGraphicsElement
{
    static constexpr TCHAR szName[] = TEXT("Local\\acpmf_graphics");
public:
    SMGraphicsElement() : MapFile(getMapFile()), rawData(getRawData()) {}
    ~SMGraphicsElement() {
        UnmapViewOfFile(rawData);
        CloseHandle(MapFile);
    }
    HANDLE MapFile;
    ACC::SPageFileGraphic* rawData;
private:
    HANDLE getMapFile() {
        auto MapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(ACC::SPageFileGraphic), szName);
        if (!MapFile)
            throw "Create Graphic Mapping Fail";
        else
            return MapFile;
    }
    ACC::SPageFileGraphic* getRawData() {
        auto rawData = static_cast<ACC::SPageFileGraphic*>(MapViewOfFile(MapFile, FILE_MAP_READ, 0, 0, sizeof(ACC::SPageFileGraphic)));
        if (!rawData)
            throw "Mapping Fail";
        else
            return rawData;
    }
};

class SMPysicsElement
{
    static constexpr TCHAR szName[] = TEXT("Local\\acpmf_physics");
public:
    SMPysicsElement() : MapFile(getMapFile()), rawData(getRawData()) {}
    ~SMPysicsElement() {
        UnmapViewOfFile(rawData);
        CloseHandle(MapFile);
    }
    HANDLE MapFile;
    ACC::SPageFilePhysics* rawData;
private:
    HANDLE getMapFile() {
        auto MapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(ACC::SPageFilePhysics), szName);
        if (!MapFile)
            throw "Create Graphic Mapping Fail";
        else
            return MapFile;
    }
    ACC::SPageFilePhysics* getRawData() {
        auto rawData = static_cast<ACC::SPageFilePhysics*>(MapViewOfFile(MapFile, FILE_MAP_READ, 0, 0, sizeof(ACC::SPageFilePhysics)));
        if (!rawData)
            throw "Mapping Fail";
        else
            return rawData;
    }
};

class SMStaticElement
{
    static constexpr TCHAR szName[] = TEXT("Local\\acpmf_static");
public:
    SMStaticElement() : MapFile(getMapFile()), rawData(getRawData()) {}
    ~SMStaticElement() {
        UnmapViewOfFile(rawData);
        CloseHandle(MapFile);
    }
    HANDLE MapFile;
    ACC::SPageFileStatic* rawData;
private:
    HANDLE getMapFile() {
        auto MapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(ACC::SPageFileStatic), szName);
        if (!MapFile)
            throw "Create Graphic Mapping Fail";
        else
            return MapFile;
    }
    ACC::SPageFileStatic* getRawData() {
        auto rawData = static_cast<ACC::SPageFileStatic*>(MapViewOfFile(MapFile, FILE_MAP_READ, 0, 0, sizeof(ACC::SPageFileStatic)));
        if (!rawData)
            throw "Mapping Fail";
        else
            return rawData;
    }
};


void ACCTelemetryDataCapturer::captureAndCompare()
{
    auto Graphic = m_graphics->rawData;
    auto Physics = m_physics->rawData;
    auto Static = m_static->rawData;

    QMap<QString,QVariant> changeData;
    const auto& lastData = this->lastTelemetryData.get();

    auto checkAndInsert = [&](auto rawDataProperty, const QString& subjectPath) {
        if (auto iter = lastData.find(subjectPath);
                iter == lastData.end() || *iter != rawDataProperty)
        {
            changeData.insert(subjectPath, rawDataProperty);
        }
    };
    checkAndInsert(Physics->speedKmh * 0.62, "SpeedMph");
    checkAndInsert(Physics->speedKmh, "SpeedKmh");
    checkAndInsert(Physics->speedKmh / 3.6 , "SpeedMs");
    checkAndInsert(Physics->rpms, "Rpm");
    checkAndInsert(Static->maxRpm, "MaxRpm");
    checkAndInsert(Physics->gear - 1, "Gear");
    if(Static->maxFuel > 0.0f) checkAndInsert(floor(Physics->fuel / Static->maxFuel * 100), "FuelRemainder");
    checkAndInsert(Physics->abs, "ABSActive");
    checkAndInsert(Physics->tc, "TCActive");
    checkAndInsert(Physics->gas,"Throttle");
    checkAndInsert(Physics->brake,"Brake");
    checkAndInsert(Physics->clutch,"Clutch");

    checkAndInsert(Graphic->completedLaps + 1, "Lap");
    checkAndInsert(Graphic->position, "Pos");
    checkAndInsert(Static->numCars, "CarCount");
    checkAndInsert(Graphic->numberOfLaps, "LapCount");

    checkAndInsert(Graphic->iLastTime / 1000.0f, "LastLapTime");
    checkAndInsert(Graphic->iBestTime / 1000.0f, "BestLapTime");
    checkAndInsert(Physics->performanceMeter, "GAP");
    checkAndInsert(Physics->performanceMeter + Graphic->iBestTime / 1000.0f, "EstimatedLapTime");


    checkAndInsert(Physics->tyreWear[TYRE_FRONT_LEFT], "TyreWearFrontLeft");
    checkAndInsert(Physics->tyreWear[TYRE_FRONT_RIGHT], "TyreWearFrontRight");
    checkAndInsert(Physics->tyreWear[TYRE_REAR_LEFT], "TyreWearRearLeft");
    checkAndInsert(Physics->tyreWear[TYRE_REAR_RIGHT], "TyreWearRearRight");

    checkAndInsert(Physics->tyreCoreTemperature[TYRE_FRONT_LEFT], "TyreTempFrontLeft");
    checkAndInsert(Physics->tyreCoreTemperature[TYRE_FRONT_RIGHT], "TyreTempFrontRight");
    checkAndInsert(Physics->tyreCoreTemperature[TYRE_REAR_LEFT], "TyreTempRearLeft");
    checkAndInsert(Physics->tyreCoreTemperature[TYRE_REAR_RIGHT], "TyreTempRearRight");

    checkAndInsert(Physics->wheelsPressure[TYRE_FRONT_LEFT], "TyrePressureFrontLeft");
    checkAndInsert(Physics->wheelsPressure[TYRE_FRONT_RIGHT], "TyrePressureFrontRight");
    checkAndInsert(Physics->wheelsPressure[TYRE_REAR_LEFT], "TyrePressureRearLeft");
    checkAndInsert(Physics->wheelsPressure[TYRE_REAR_RIGHT], "TyrePressureRearRight");

    Capturer::lastTelemetryData.update(changeData);
}

void ACCTelemetryDataCapturer::run()
try{
    m_graphics.reset(new SMGraphicsElement());
    m_physics.reset(new SMPysicsElement());
    m_static.reset(new SMStaticElement());

    qDebug()<<"start ACC capture!";

    while(m_flag)
    {
        captureAndCompare();
        QThread::msleep(20);
    }

    TelemetryDataBuffer::Instance().remove();
    lastTelemetryData.remove();


    m_graphics.release();
    m_physics.release();
    m_static.release();
}catch(const char *msg){
    qDebug()<<"异常："<<msg;
    return ;
}

