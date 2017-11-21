#include <os/internal/localsocketconnector.h>
#include <os/internal/localsocket.h>
#include <os/internal/moonlocalsocket.h>

#include <QDebug>
#include <QLocalSocket>

namespace moon {

std::atomic<unsigned long> LocalSocketConnector::sConnectionNo = 0;

LocalSocketPtr LocalSocketConnector::connectToServer(const QString &serverName, unsigned long timeoutMillis){
    if (serverName.isEmpty()){
        qDebug() << "LocalSocketConnector::connectToServer failed, serverName should not be empty.";
        return LocalSocketPtr();
    }

    const QString connectionName = QString("%1-client-%2").arg(serverName).arg(++sConnectionNo);
    QLocalSocket *socket = new QLocalSocket();
    socket->connectToServer(serverName);
    if (!socket->waitForConnected(timeoutMillis)){
        qDebug() << "LocalSocketConnector::connectToServer failed, waitForConnected failed.";
        delete socket;
        return LocalSocketPtr();
    }

    return LocalSocket::create(connectionName, socket);
}





}  // ~moon


