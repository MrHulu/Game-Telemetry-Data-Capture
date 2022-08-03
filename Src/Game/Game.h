#pragma once

#include <QSet>
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    ~Game();
    Q_INVOKABLE virtual void startCapturer() = 0;
    Q_INVOKABLE virtual void stopCapturer() = 0;

signals:
    void errorOccurred(const QString& message);

    //游戏名称
public:
    Q_PROPERTY(QString name READ name CONSTANT)
    QString name() const;
protected:
    QString         m_name;

    //游戏是否运行
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
public:
    bool isRunning() const;
    void setIsRunning(bool newIsRunning);
signals:
    void isRunningChanged();
protected:
    bool            m_isRunning = false;

    //数据采集方式
public:
    enum CaptureMethod
    {
        None = 0,
        NetWorkUDP,
        SharedMemory,
        UDPAndSM,
        Other,
    };
    Q_ENUM(CaptureMethod)
    Q_PROPERTY(CaptureMethod captureMethod READ captureMethod CONSTANT)
    CaptureMethod captureMethod() const { return m_captureMethod; }
protected:
    CaptureMethod   m_captureMethod = None;

    //进程名称
public:
    QSet<QString>   processNames() const;
    void setProcessNames(const QSet<QString>& names);
protected:
    QSet<QString>   m_processName;

    //安装路径
    Q_PROPERTY(QString installPath READ installPath WRITE setInstallPath NOTIFY installPathChanged)
public:
    QString installPath() const;;
    void setInstallPath(const QString& newInstallPath);
signals:
    void installPathChanged();
protected:
    QString m_installPath;

};


inline QString Game::name() const { return m_name; }

inline bool Game::isRunning() const { return m_isRunning; }

inline QSet<QString> Game::processNames() const { return m_processName; }

inline QString Game::installPath() const { return m_installPath; }

