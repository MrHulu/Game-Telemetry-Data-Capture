#include <QtTest>
#include <QSignalSpy>
#include <QMap>
#include <memory>

// add necessary includes here
#include "Game/GameInfoHelper.h"
#include "Game/DiRT 4/Dirt4Game.h"

class tst_GameInfoReadWrite : public QObject
{
    Q_OBJECT
public:
    tst_GameInfoReadWrite();

private slots:
    void checkReadGameInfoFile();
    void checkWriteGameInfoFile();

private:
    Dirt4Game*  dirt4{};
    GameInfoHelper* helper{};
};

tst_GameInfoReadWrite::tst_GameInfoReadWrite()
{
    dirt4 = new Dirt4Game(this);
    helper = new GameInfoHelper(QMap<QString, Game*>{ {dirt4->name(), dirt4} });
}


void tst_GameInfoReadWrite::checkReadGameInfoFile()
{
    QCOMPARE(dirt4->readPort(), 21466);
    QCOMPARE(dirt4->writePort(), 21400);
    QCOMPARE(dirt4->installPath(), nullptr);
    QCOMPARE(dirt4->processNames(), QSet<QString>{"dirt4.exe"});

    QSignalSpy spy(dirt4, &Dirt4Game::readPortChanged);
    spy.wait(500);
    helper->updateGameInfo();
    QCOMPARE(dirt4->readPort(), 20777);
}

void tst_GameInfoReadWrite::checkWriteGameInfoFile()
{
    QCOMPARE(dirt4->installPath(), nullptr);

    // 修改 installPath 为 C:\\test\\dirt4.exe
    QSignalSpy spy(dirt4, &Dirt4Game::installPathChanged);
    spy.wait(200);
    helper->writeGameInstallPathInfo(dirt4->name(), "C:\\test\\dirt4.exe");
    helper->updateGameInfo();
    QCOMPARE(dirt4->installPath(), "C:\\test\\dirt4.exe");

    // 恢复
    spy.clear();
    helper->writeGameInstallPathInfo(dirt4->name(), nullptr);
    helper->updateGameInfo();
    spy.wait(200);
    QCOMPARE(dirt4->installPath(), nullptr);
}







QTEST_MAIN(tst_GameInfoReadWrite)

#include "tst_GameInfoReadWrite.moc"
