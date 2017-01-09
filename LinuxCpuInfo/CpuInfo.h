#ifndef CPUINFO_H
#define CPUINFO_H

// QT Includes
#include <QObject>
#include <QTextStream>

class CpuInfo : public QObject
{
    Q_OBJECT
public:
    static CpuInfo* getInstance();
    bool loadCpuInfo(const QString& cpuInfoPath);
    QList<QStringList> cpuInfoList();
    int processorCount();

signals:

public slots:

private:
    Q_DISABLE_COPY(CpuInfo);
    explicit CpuInfo(QObject *parent = 0);

    static CpuInfo *m_cpuInfo;
    QList<QStringList> m_cpuInfoList;
    void processCpuInfoTextStream(QTextStream& cpuInfoTS);
};

#endif // CPUINFO_H
