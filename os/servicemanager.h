#ifndef PLATFORM_OS_SERVICEMANAGER_H
#define PLATFORM_OS_SERVICEMANAGER_H

#include <QMap>
#include <QMutex>
#include <QString>

namespace moon {

class LocalService;

class ServiceManager
{
public:
    ~ServiceManager();
    static ServiceManager& getInstance();
    void startService(LocalService *service);
    void stopService(LocalService *service);
    void stopService(const QString &serviceName);
private:
    ServiceManager();
private:
    static QMutex sLock;
    static ServiceManager *sServiceManager;
    QMap<QString, LocalService*> mServices;

};


} // ~moon

#endif // PLATFORM_OS_SERVICEMANAGER_H

