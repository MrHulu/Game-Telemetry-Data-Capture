#include <QtTest>
#include <QSignalSpy>

// add necessary includes here
#include "Game/Assetto Corsa/ACGame.h"
#include "Game/GameRunMonitoringHelper.h"
#include "Game/TelemetryDataBuffer.h"

#include <memory>

class tst_GameRunMonitoring : public QObject
{
    Q_OBJECT
public:
    tst_GameRunMonitoring();
    ~tst_GameRunMonitoring();

private slots:
    void tst_MonitoringNoRunning();
    void tst_MonitoringRunning();

private:
    ACGame* ac;
    GameRunMonitoringHelper* helper;
    Game* currentRunGame;
    bool isReceiveGameRunSignal = false;
};

tst_GameRunMonitoring::tst_GameRunMonitoring() : ac(new ACGame(this))
{
    helper = new GameRunMonitoringHelper(QMap<QString, Game*>{ {ac->name(), ac} });
    connect(helper, &GameRunMonitoringHelper::gameIsRunning, this, [this](Game* game) {
        currentRunGame = game;
        isReceiveGameRunSignal = true;
    });

}

tst_GameRunMonitoring::~tst_GameRunMonitoring()
{

}

void tst_GameRunMonitoring::tst_MonitoringNoRunning()
{

    isReceiveGameRunSignal = false;
    QSignalSpy spy(helper, &GameRunMonitoringHelper::gameIsRunning);
    if(!spy.wait(2000))
        QFAIL("无法启动监控!");
    QVERIFY(isReceiveGameRunSignal);
    QCOMPARE(currentRunGame, nullptr);

}

void tst_GameRunMonitoring::tst_MonitoringRunning()
{
    isReceiveGameRunSignal = false;
    QSignalSpy spy(helper, &GameRunMonitoringHelper::gameIsRunning);
    ac->setProcessNames(QSet<QString>{ "tst_GameRunMonitoring.exe" });
    if(!spy.wait(2000))
        QFAIL("无法启动监控!");
    QVERIFY(isReceiveGameRunSignal);
    QCOMPARE(currentRunGame, ac);
}





QTEST_MAIN(tst_GameRunMonitoring)

#include "tst_GameRunMonitoring.moc"
