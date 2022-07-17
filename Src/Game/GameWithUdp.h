#pragma once

#include "Game/Game.h"

class GameWithUdp : public Game
{
    Q_OBJECT

    //UDP ReadPort
    Q_PROPERTY(int readPort READ readPort WRITE setReadPort NOTIFY readPortChanged)
public:
    int readPort() const;
    void setReadPort(int newReadPort);
    void updateReadPort(int newReadPort);
signals:
    void readPortChanged();
private:
    int m_readPort = 21466;

    //UDP WritePort
    Q_PROPERTY(int writePort READ writePort WRITE setWritePort NOTIFY writePortChanged)
public:
    int writePort() const;
    void setWritePort(int newWritePort);
    void updateWritePort(int newWritePort);
signals:
    void writePortChanged();
private:
    int m_writePort = 21400;

    //UDP ReadAddress
    Q_PROPERTY(QString readAddress READ readAddress WRITE setReadAddress NOTIFY readAddressChanged)
public:
    QString readAddress() const;
    void setReadAddress(QString newReadAddress);
    void updateReadAddress(QString newReadAddress);
signals:
    void readAddressChanged();
private:
    QString m_readAddress;

    //UDP WriteAddress
    Q_PROPERTY(QString writeAddress READ writeAddress WRITE setWriteAddress NOTIFY writeAddressChanged)
public:
    QString writeAddress() const;
    void setWriteAddress(QString newWriteAddress);
    void updateWriteAddress(QString newWriteAddress);
signals:
    void writeAddressChanged();
private:
    QString m_writeAddress;

public:
    explicit GameWithUdp(QObject *parent = nullptr);
};

inline int GameWithUdp::readPort() const { return m_readPort; }
inline int GameWithUdp::writePort() const { return m_writePort; }
inline QString GameWithUdp::readAddress() const { return m_readAddress; }
inline QString GameWithUdp::writeAddress() const { return m_writeAddress; }
