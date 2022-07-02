#pragma once

#include "Game/Capturer.h"

#include <QHostAddress>
#include <QUdpSocket>

class CapturerWithUdp : public Capturer
{
public:
    CapturerWithUdp(QObject *parent = nullptr);
    ~CapturerWithUdp();
    void setUdpInfoInCapturer(quint16 port, QString address = "127.0.0.1");
    void setUdpInfoInForward(quint16 port, QString address = "127.0.0.1");

protected:
    bool bind();
    QByteArray capturing();
    qint64 forwarding(const QByteArray& data);

protected:
    QUdpSocket*     m_socket = nullptr;

    /* Capturer */
    quint16         m_capturerPort = 21466;
    QHostAddress    m_capturerAddress = QHostAddress::LocalHost;

    /* Forward */
    quint16         m_forwardPort = 21400;
    QHostAddress    m_forwardAddress = QHostAddress::LocalHost;
};

