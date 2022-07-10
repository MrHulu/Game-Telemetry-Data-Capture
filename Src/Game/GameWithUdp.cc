#include "Game/GameWithUdp.h"
#include <QThread>

void GameWithUdp::setReadPort(int newReadPort)
{
    if(m_readPort == newReadPort)
        return;
    updateReadPort(newReadPort);
}

void GameWithUdp::updateReadPort(int newReadPort)
{
    if(m_readPort == newReadPort)
        return;
    if(isRunnig()) {
        emit errorOccurred(QString("Game is Running! Can`t Update Address Or Port!"));
        return;
    }
    m_readPort = newReadPort;
    emit readPortChanged();
}

void GameWithUdp::setWritePort(int newWritePort)
{
    if(m_writePort == newWritePort)
        return;
    updateWritePort(newWritePort);
}

void GameWithUdp::updateWritePort(int newWritePort)
{
    if(m_writePort == newWritePort)
        return;
    if(isRunnig()) {
        emit errorOccurred(QString("Game is Running! Can`t Update Address Or Port!"));
        return;
    }
    m_writePort = newWritePort;
    emit writePortChanged();
}

void GameWithUdp::setReadAddress(QString newReadAddress)
{
    if(m_readAddress == newReadAddress)
        return;
    updateReadAddress(newReadAddress);
}

void GameWithUdp::updateReadAddress(QString newReadAddress)
{
    if(m_readAddress == newReadAddress)
        return;
    if(isRunnig()) {
        emit errorOccurred(QString("Game is Running! Can`t Update Address Or Port!"));
        return;
    }
    m_readAddress = newReadAddress;
    emit readAddressChanged();
}

void GameWithUdp::setWriteAddress(QString newWriteAddress)
{
    if(m_writeAddress == newWriteAddress)
        return;
    updateWriteAddress(newWriteAddress);
}

void GameWithUdp::updateWriteAddress(QString newWriteAddress)
{
    if(m_writeAddress == newWriteAddress)
        return;
    if(isRunnig()) {
        emit errorOccurred(QString("Game is Running! Can`t Update Address Or Port!"));
        return;
    }
    m_writeAddress = newWriteAddress;
    emit writeAddressChanged();
}

GameWithUdp::GameWithUdp(QObject *parent)
    : Game{parent}
{

}
