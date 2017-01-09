#ifndef CPUINFOMODEL_H
#define CPUINFOMODEL_H

#include <QObject>

#include <QtQml>

class Item
{
public:
    Item(const QString &info);
    QString info() const;
private:
    QString m_info;
};

/*
 * CpuInfoModel contians the model of CPU info.
*/
class CpuInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRoles {
        InfoRole = Qt::UserRole + 1
    };

    CpuInfoModel(QObject *parent = 0);
    void addItem(const Item &item);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void updateModel(int index);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Item> m_data;
};

#endif // CPUINFOMODEL_H
