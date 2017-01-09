#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <QObject>

class ComboBoxModel : public QObject
{
    Q_OBJECT
public:
    explicit ComboBoxModel(QObject *parent = 0);

    ComboBoxModel(const QStringList &list, QObject *parent = 0);

    const QStringList& comboList();
    void setComboList(const QStringList &comboList);

    int count();
    void setCount(int count);

signals:

public slots:

private:
    QStringList m_comboList;
    int         m_count;
};

#endif // COMBOBOXMODEL_H
