#pragma once

#include <QAbstractTableModel>

class TelemetryDataTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    //enum { TelemetryData = Qt::UserRole, };
    explicit TelemetryDataTableModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override { return m_datas.count(); }
    int columnCount(const QModelIndex &parent) const override { return 2; }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    //bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;    
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    void onTelemetryDataChanged(const QVariantMap& data);

private:
    QVariantMap     m_datas;
    QVariantList    m_dataKeys;
};






