#include "CpuInfo.h"

// QT includes
#include <QFile>

CpuInfo* CpuInfo::m_cpuInfo = NULL;

CpuInfo* CpuInfo::getInstance(){
    if(m_cpuInfo == NULL){
        m_cpuInfo = new CpuInfo();
    }

    return m_cpuInfo;
}

CpuInfo::CpuInfo(QObject *parent) :
                                    QObject(parent){

}

/*
    Loads cpu information from given location.
*/
bool CpuInfo::loadCpuInfo(const QString& cpuInfoPath){
    if(!m_cpuInfoList.empty())
        return true;

    bool status = true;
    QFile cpuInfoFile(cpuInfoPath);
    if ( cpuInfoFile.open(QIODevice::ReadOnly) ) {
        QTextStream cpuInfoTS(&cpuInfoFile);
        processCpuInfoTextStream(cpuInfoTS);
        cpuInfoFile.close();
    } else {
        status = false;
    }

    return status;
}

/*
   Reads text stream, parse it and appendsin the list.
   Stroing data in QList<QStringList>, each QList contains a
   QStringList for a particular processor(all its attributes).
*/
void CpuInfo::processCpuInfoTextStream(QTextStream& cpuInfoTS){
    QStringList list;
    list.append(cpuInfoTS.readLine());

    while(!cpuInfoTS.atEnd()){
        QString data = cpuInfoTS.readLine();
        if (data == ""){
            m_cpuInfoList.append(list);
            list.clear();
        } else {
            int index =  data.indexOf("\t\t:", 0);
            if(index != -1){
                data = data.remove(index, 1);
                list.append(data);
            } else {
                list.append(data);
            }
        }
    }
}

QList<QStringList> CpuInfo::cpuInfoList(){
    return m_cpuInfoList;
}

int CpuInfo::processorCount(){
    return m_cpuInfoList.count();
}
