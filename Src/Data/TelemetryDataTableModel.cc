#include "Data/TelemetryDataTableModel.h"
#include "Data/TelemetryDataBuffer.h"

TelemetryDataTableModel::TelemetryDataTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    auto& telemetryDataInstance = TelemetryDataBuffer::Instance();
    connect(&telemetryDataInstance, &TelemetryDataBuffer::messagesChanged, this, &TelemetryDataTableModel::onTelemetryDataChanged, Qt::QueuedConnection);

    // Init
    beginResetModel();
    m_datas = telemetryDataInstance.get();
    for(auto iter = m_datas.begin(); iter != m_datas.end(); iter++)
        m_dataKeys.append(iter.key());
    endResetModel();

    //保存和恢复model选中项，因为在resetModel后会失效
//    connect(model,&MyTableModel::modelAboutToBeReset,this,[=]{
//            selectedIndex=table->currentIndex();
//        },Qt::DirectConnection);
//    connect(model,&MyTableModel::modelReset,this,[=]{
//            //不用担心无效的index，接口内部会处理
//            table->setCurrentIndex(selectedIndex);
//        },Qt::DirectConnection);
}

QVariant TelemetryDataTableModel::data(const QModelIndex &index, int role) const
{
    auto column = index.column();
    auto row = index.row();
    switch (role) {
    default: break;
    case Qt::DisplayRole:
        auto telemetryName = m_dataKeys[row].toString();
        if(column == 0)  return telemetryName;
        else  return m_datas[telemetryName];
    }
    return QVariant();
}

QHash<int, QByteArray> TelemetryDataTableModel::roleNames() const
{
    return QHash<int, QByteArray> {
            {Qt::DisplayRole, "display"}
    };
}

void TelemetryDataTableModel::onTelemetryDataChanged(const QVariantMap &data)
{
    beginResetModel();
    m_datas = data;
    m_dataKeys.clear();
    for(auto iter = m_datas.begin(); iter != m_datas.end(); iter++)
        m_dataKeys.append(iter.key());
    endResetModel();
}

Qt::ItemFlags TelemetryDataTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}
