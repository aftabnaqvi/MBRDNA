#include <QGuiApplication>
#include <QQmlApplicationEngine>

//project includes
#include "CpuInfo.h"
#include "CpuInfoModel.h"

//QML includes
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>

//QT includes
#include <QStringList>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CpuInfo *cpuInfo = CpuInfo::getInstance();
    cpuInfo->loadCpuInfo(QString("/proc/cpuinfo"));

    QStringList processorList;
    for(int i=0; i<cpuInfo->processorCount(); i++){
        processorList<<QString("Processor : %1").arg(i);
    }

    CpuInfoModel cpuModel;
    QQmlContext *ownContext = engine.rootContext();
    ownContext->setContextProperty("comboModel", QVariant::fromValue(processorList));
    ownContext->setContextProperty("cpuModel", &cpuModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
