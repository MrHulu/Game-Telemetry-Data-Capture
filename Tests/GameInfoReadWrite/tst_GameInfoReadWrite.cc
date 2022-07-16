#include <QtTest>
#include <QSignalSpy>

// add necessary includes here
#include "Game/GameInfoHelper.h"
#include "Game/DiRT 4/Dirt4Game.h"

#include <memory>

class tst_GameInfoReadWrite : public QObject
{
    Q_OBJECT
public:
    tst_GameInfoReadWrite();

private slots:
    void checkEmbeddeGameInfoFile();
    void createLocalGameInfoFile();

private:
    Dirt4Game*  dirt4{};
};

tst_GameInfoReadWrite::tst_GameInfoReadWrite()
{
    dirt4 = new Dirt4Game(this);
}

void tst_GameInfoReadWrite::checkEmbeddeGameInfoFile()
{

}

void tst_GameInfoReadWrite::createLocalGameInfoFile()
{

}







QTEST_MAIN(tst_GameInfoReadWrite)

#include "tst_GameInfoReadWrite.moc"
