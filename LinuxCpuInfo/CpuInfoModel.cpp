#include "CpuInfoModel.h"

// Project Inculdes
#include "CpuInfo.h"

Item::Item(const QString &info)
                    : m_info(info){
}

QString Item::info() const{
    return m_info;
}

CpuInfoModel::CpuInfoModel(QObject *parent)
                                        : QAbstractListModel(parent){
}

void CpuInfoModel::addItem(const Item &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << item;
    endInsertRows();
}

int CpuInfoModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant CpuInfoModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();

    const Item &item = m_data[index.row()];
    if (role == InfoRole)
        return item.info();

    return QVariant();
}

void CpuInfoModel::updateModel(int index){
    // removing existing rows from model.
    this->beginRemoveRows(QModelIndex(), 0, m_data.count());
    this->removeRows(0, m_data.count());
    this->endRemoveRows();

    m_data.clear();
    CpuInfo *cpuInfo = CpuInfo::getInstance();
    cpuInfo->loadCpuInfo(QString("/proc/cpuinfo"));
    QList<QStringList> cpuData = cpuInfo->cpuInfoList();

    // adding new rows in the model.
    this->beginInsertRows(QModelIndex(), 0, 0);
    foreach(const QString data, cpuData[index]){
        addItem(data);
    }
    this->endInsertRows();
}

QHash<int, QByteArray> CpuInfoModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[InfoRole] = "Info";

    return roles;
}
