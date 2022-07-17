#pragma once

#include "Game/Capturer.h"

#include <QHostAddress>
#include <QUdpSocket>

class CapturerWithUdp : public Capturer
{
public:
    CapturerWithUdp(QObject *parent = nullptr);
    ~CapturerWithUdp();

    void setCapturePort(quint16 port);
    void setCaptureAddress(const QString& address = "127.0.0.1");

    void setForwardPort(quint16 port);
    void setForwardAddress(const QString& address = "127.0.0.1");

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

inline void CapturerWithUdp::setCapturePort(quint16 port) { m_capturerPort = port; }

inline void CapturerWithUdp::setCaptureAddress(const QString &address) { m_capturerAddress.setAddress(address); }

inline void CapturerWithUdp::setForwardPort(quint16 port) { m_forwardPort = port; }

inline void CapturerWithUdp::setForwardAddress(const QString &address) { m_forwardAddress.setAddress(address); }

