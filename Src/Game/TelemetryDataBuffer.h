#pragma once

#include <QObject>
#include <QMap>
#include <QVariant>

class TelemetryDataBuffer : public QObject
{
    Q_OBJECT
public:
    TelemetryDataBuffer();
    static TelemetryDataBuffer& Instance();

signals:
    void messagesChanged(QMap<QString,QVariant> data);

public slots:
    void update(QMap<QString,QVariant> data);
    void remove();
    const QMap<QString, QVariant>& get(void);

private:
    static TelemetryDataBuffer _instance;
    QMap<QString, QVariant> m_data;
};



inline TelemetryDataBuffer::TelemetryDataBuffer()
{
    m_data.clear();
}
