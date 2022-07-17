#include "Game/CapturerWithUdp.h"

#include <QDebug>

CapturerWithUdp::CapturerWithUdp(QObject *parent)
{
    m_socket = new QUdpSocket();
}

CapturerWithUdp::~CapturerWithUdp()
{
    if(m_socket) {
        m_socket->close();
        m_socket->deleteLater();
    }
}

bool CapturerWithUdp::bind()
{
    return m_socket->bind(m_capturerAddress, m_capturerPort);
}

QByteArray CapturerWithUdp::capturing()
{
    QByteArray pendingReadData;
    if(m_socket->hasPendingDatagrams()) {
        pendingReadData.resize(m_socket->pendingDatagramSize());
        int ret= m_socket->readDatagram(pendingReadData.data(), pendingReadData.size());
        if(ret == -1) {
            qWarning() << QString("[Error] Udp(Port:%1 Address:%2) Read error: %1")
                          .arg(m_socket->errorString())
                          .arg(m_capturerPort)
                          .arg(m_capturerAddress.toString());
        }
    }
    return pendingReadData;
}

qint64 CapturerWithUdp::forwarding(const QByteArray& data)
{
     return m_socket->writeDatagram(data, data.size(), m_forwardAddress, m_forwardPort);
}
