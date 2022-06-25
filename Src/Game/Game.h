#pragma once

#include <QSet>
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    Q_INVOKABLE virtual void startCapturer() = 0;
    Q_INVOKABLE virtual void stopCapturer() = 0;

    //游戏名称
public:
    Q_PROPERTY(QString name READ name CONSTANT)
    const QString&  name() const { return m_name; }
protected:
    QString         m_name;

    //游戏是否运行
public:
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
    bool isRunnig() const { return m_isRunning; }
    void setIsRunnig(bool newIsRunning);
signals:
    void isRunningChanged();
protected:
    bool            m_isRunning = false;

//    //数据采集方式
//public:
//    enum CaptureMethod
//    {
//        None = 0,
//        NetWorkUDP,
//        SharedMemory,
//        UDPAndSM,
//        Other,
//    };
//    Q_ENUMS(CaptureMethod)
//    Q_PROPERTY(CaptureMethod captureMethod READ captureMethod CONSTANT)
//protected:
//    CaptureMethod   m_captureMethod = None;

    //进程名称
public:
    const QSet<QString>&    processNames() const;
    void setProcessNames(const QSet<QString>& names);
protected:
    QSet<QString>   m_processName;

};

