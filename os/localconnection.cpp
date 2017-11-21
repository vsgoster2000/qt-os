#include <os/localconnection.h>
#include <os/internal/localsocketconnector.h>

namespace moon{

LocalConnectionPtr LocalConnection::connectToServer(const QString &serviceName, unsigned long timeoutMillis){
    return LocalConnection::create(LocalSocketConnector::connectToServer(serviceName, timeoutMillis));
}

LocalConnection::LocalConnection(LocalSocketPtr localSocket) : mLocalSocket(localSocket) {
mLocalSocket->setOnDataReceivedListener(std::bind(&LocalConnection::onData, this, std::placeholders::_1));
}

LocalConnection::~LocalConnection()
{

}

void LocalConnection::onData(const QByteArray &data){
    if (mOnNewMessageListener){
       mOnNewMessageListener(LocalMessage::create(data));
    }
}




}  // ~moon
