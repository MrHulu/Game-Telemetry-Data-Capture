#include "Data/TelemetryDataTableModel.h"
#include "Data/TelemetryDataBuffer.h"

TelemetryDataTableModel::TelemetryDataTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    auto& telemetryDataInstance = TelemetryDataBuffer::Instance();
    connect(&telemetryDataInstance, &TelemetryDataBuffer::messagesChanged, this, &TelemetryDataTableModel::onTelemetryDataChanged, Qt::QueuedConnection);

    // Init
    m_datas = telemetryDataInstance.get();
    for(auto iter = m_datas.begin(); iter != m_datas.end(); iter++) {
        beginInsertRows(QModelIndex(), m_dataKeys.size(), m_dataKeys.size());
        m_dataKeys.append(iter.key());
        endInsertRows();
    }
}

QVariant TelemetryDataTableModel::data(const QModelIndex &index, int role) const
{
    auto column = index.column();
    auto row = index.row();
    switch (role) {
    default: break;
    case TelemetryData:
        auto telemetryName = m_dataKeys[row].toString();
        if(column == 0)  return telemetryName;
        else  return m_datas[telemetryName];
    }
    return QVariant();
}

QHash<int, QByteArray> TelemetryDataTableModel::roleNames() const
{
    return QHash<int, QByteArray> {
            {TelemetryData, "telemetryData"}
    };
}

void TelemetryDataTableModel::onTelemetryDataChanged(const QVariantMap &data)
{

}
