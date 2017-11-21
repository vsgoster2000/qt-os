#include <os/localconnectionconnector.h>
#include <os/localconnection.h>

#include <QDebug>

namespace moon{

QMutex LocalConnectionConnector::sSingleLock;
LocalConnectionConnector *LocalConnectionConnector::sInstance;

LocalConnectionPtr LocalConnectionConnector::connectToServer(const QString &serviceName){
    if (serviceName.isEmpty()){
        qDebug() << "LocalConnectionConnector::connectToServer failed, serviceName should not be empty.";
        return NULL;
    }

    QLocalSocket *socket = new QLocalSocket();

    socket->connectToServer(serviceName);
    if (!socket->waitForConnected(LocalConnection::kConnectTimeoutUsec)){
        qDebug() << "LocalConnectionConnector::connectToServer failed, waitForConnected failed.";
        delete socket;
        return NULL;
    }

    QString connectionName = QString("%1-client-%2").arg(serviceName).arg(mConnectionNo);
    LocalConnectionPtr conn(new LocalConnection(connectionName, socket));

//    QObject::connect(socket, &QLocalSocket::disconnected, [this](){

//    });

    mConnections.insert(connectionName, conn);
    return conn;
}

LocalConnectionConnector::LocalConnectionConnector() {

}

//void LocalConnectionConnector::onDisconnected(const QString &connName) {
//    //int ret = mConnections.remove(connName);
//    Q_ASSERT(1 == ret);


//}


}  // ~moon
