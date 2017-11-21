#include <os/servicemanager.h>

#include <os/localservice.h>

#include <QDebug>
#include <QMutexLocker>

namespace moon {

QMutex ServiceManager::sLock;
ServiceManager *ServiceManager::sServiceManager = NULL;

ServiceManager::ServiceManager() {

}

ServiceManager::~ServiceManager() {

}

ServiceManager &ServiceManager::getInstance() {
    if (NULL == sServiceManager){
        QMutexLocker locker(&sLock);
        if (NULL == sServiceManager){
            sServiceManager = new ServiceManager();
        }
    }

    return *sServiceManager;
}

void ServiceManager::startService(LocalService *service) {
    if (NULL == service){
        qWarning() << "ServiceManager::startService failed, argument service should not be NULL.";
        return ;
    }

    {
        QMutexLocker locker(&sLock);
        if (mServices.contains(service->getName())){
            qWarning() << "ServiceManager::startService failed, service:" << service->getName() << " has already started.";
            return ;
        }

        mServices.insert(service->getName(), service);
    }

    service->startService();
}

void ServiceManager::stopService(LocalService *service) {
    if (NULL == service){
        qWarning() << "ServiceManager::stopService failed, argument service should not be NULL.";
        return ;
    }

    stopService(service->getName());
}

void ServiceManager::stopService(const QString &serviceName) {
    {
        QMutexLocker locker(&sLock);
        if (!mServices.contains(serviceName)){
            qWarning() << "ServiceManager::stopService failed, service:" << serviceName << " not started.";
            return ;
        }

        LocalService *service = mServices.value(serviceName, NULL);
        Q_ASSERT(NULL != service);
        service->stopService();
        mServices.remove(serviceName);
    }
}


}
