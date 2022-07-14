#include <QtTest>
#include <QSignalSpy>

// add necessary includes here
#include "Game/GameInfoHelper.h"

#include <memory>

class tst_GameInfoReadWrite : public QObject
{
    Q_OBJECT
public:
    tst_GameInfoReadWrite();
    ~tst_GameInfoReadWrite();

private slots:

private:
};

tst_GameInfoReadWrite::tst_GameInfoReadWrite()
{


}

tst_GameInfoReadWrite::~tst_GameInfoReadWrite()
{

}







QTEST_MAIN(tst_GameInfoReadWrite)

#include "tst_GameInfoReadWrite.moc"
