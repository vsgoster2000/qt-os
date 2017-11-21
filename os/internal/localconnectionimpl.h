#ifndef PLATFORM_OS_INTERNAL_LOCALCONNECTIONIMPL_H
#define PLATFORM_OS_INTERNAL_LOCALCONNECTIONIMPL_H

#include <os/internal/internaldefine.h>
#include <os/internal/localsocket.h>
#include <os/localconnection.h>

namespace moon {

class LocalConnectionImpl
{
public:
    LocalConnectionImpl(LocalSocketPtr localSocket);
    virtual ~LocalConnectionImpl();

    virtual bool send(const QByteArray &data, unsigned long timeoutUsec) {
        Q_ASSERT(mLocalSocket);
        if (mLocalSocket->isConnected()){
            return mLocalSocket->send(data, timeoutUsec);
        }
        return false;
    }

    virtual QByteArray recv(unsigned long timeoutUsec) {
        Q_ASSERT(mLocalSocket);
        if (mLocalSocket->isConnected()){
            return mLocalSocket->recv(timeoutUsec);
        }

        return false;
    }

    virtual void close() {
        Q_ASSERT(mLocalSocket);
        mLocalSocket->closed();
    }

    virtual bool isConnected() const {
        Q_ASSERT(mLocalSocket);
        return mLocalSocket->isConnected();
     }

    virtual const QString& getName() const {
        Q_ASSERT(mLocalSocket);
        return mLocalSocket->getName();
    }

    virtual const QString& getErrorString() const {
        Q_ASSERT(mLocalSocket);
        return mLocalSocket->getErrorString();
    }
private:
    LocalSocketPtr mLocalSocket;
};


}  // ~moon

#endif // PLATFORM_OS_INTERNAL_LOCALCONNECTIONIMPL_H
