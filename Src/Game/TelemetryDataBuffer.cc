#include "Game/TelemetryDataBuffer.h"

TelemetryDataBuffer TelemetryDataBuffer::_instance;

TelemetryDataBuffer &TelemetryDataBuffer::Instance()
{
    return _instance;
}

void TelemetryDataBuffer::update(QMap<QString, QVariant> data)
{
    m_data.insert(data);
    emit messagesChanged(data);
}

void TelemetryDataBuffer::remove()
{
    for(auto iter = m_data.begin(); iter != m_data.end(); ++iter) {
        iter.value() = QVariant();
    }
    emit messagesChanged(m_data);
    m_data.clear();
}

const QMap<QString, QVariant> &TelemetryDataBuffer::get()
{
    return m_data;
}
