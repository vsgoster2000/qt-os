#ifndef PLATFORM_OS_LOCALCONNECTIONCONNECTOR_H
#define PLATFORM_OS_LOCALCONNECTIONCONNECTOR_H

#include <os/localconnectiondefine.h>

#include <QMap>
#include <QMutex>
#include <QString>

QT_BEGIN_NAMESPACE
class QLocalSocket;
QT_END_NAMESPACE

namespace moon {

class LocalConnectionConnector
{
public:
    LocalConnectionPtr connectToServer(const QString &serviceName);

    static LocalConnectionConnector& getInstance(){
        if (NULL == sInstance){
            sSingleLock.lock();
            if (NULL == sInstance){
                sInstance = new LocalConnectionConnector();
            }
            sSingleLock.unlock();
        }
        return *sInstance;
    }

private:
    LocalConnectionConnector();
    unsigned long getAndIncreaseNo(){
        mLock.lock();
        unsigned long lastNo = mConnectionNo;
        ++mConnectionNo;
        mLock.unlock();

        return lastNo;
    }

private:    
    static QMutex sSingleLock;
    static LocalConnectionConnector *sInstance;

    unsigned long mConnectionNo;
    QMutex mLock;
    QMap<QString, LocalConnectionPtr > mConnections;
};


}  // ~moon

#endif // PLATFORM_OS_LOCALCONNECTIONCONNECTOR_H
