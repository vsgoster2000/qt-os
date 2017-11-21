#include <os/localservice.h>
#include <os/internal/localsocket.h>
#include <os/internal/localserver.h>

#include <functional>

#include <QDebug>
#include <QLocalSocket>

namespace moon {

class DeleteAttacher : public QObject{
public:
    DeleteAttacher(const LocalSocketPtr &tmp) : mTmp(tmp){
    }

    ~DeleteAttacher() {
    }

private:
    LocalSocketPtr mTmp;
};

LocalService::LocalService(){
    mLocalServer = NULL;
    connect(this, &LocalService::sendMessageSignal, this, &LocalService::sSendMessage);
}

LocalService::~LocalService(){
    Q_ASSERT(NULL != mLocalServer);
    delete mLocalServer;
    mLocalServer = NULL;
}

bool LocalService::startService() {
    mLocalServer = new LocalServer(getName());
    mLocalServer->setOnNewConnectionListener(std::bind(&LocalService::sNewConnection, this, std::placeholders::_1));
    Q_ASSERT(NULL != mLocalServer);
    if (!mLocalServer->start()){
        onStartFailed(mLocalServer->errorString());
        return false;
    }

    onStart();
    return true;
}

void LocalService::stopService() {
    Q_ASSERT(NULL != mLocalServer);
    mLocalServer->stop();
    mConnections.clear();
    onStop();
}

void LocalService::sNewConnection(const LocalSocketPtr &conn){
    Q_ASSERT(!mConnections.contains(conn->getName()));
    mConnections.insert(conn->getName(), conn);

    conn->setOnDataReceivedListener(std::bind(&LocalService::sNewMessage, this, conn->getName(), std::placeholders::_1));
    conn->setOnDisconnectedListener(std::bind(&LocalService::sDisconnection, this, conn->getName()));

    onNewConnection(conn->getName());
}

void LocalService::sDisconnection(const QString &name) {
    qDebug() << "LocalService::onDisconnection, name:" << name;
    LocalSocketPtr ptr = mConnections.value(name, LocalSocketPtr());
    Q_ASSERT(ptr);
    Q_ASSERT(!ptr->isConnected());

    mConnections.remove(name);
    onDisconnected(name);

    DeleteAttacher *attach = new DeleteAttacher(ptr);
    attach->deleteLater();
}

void LocalService::sNewMessage(const QString name, const QByteArray &data) {
    LocalMessage msg = LocalMessage::create(data);
    msg.replyTo = name;
    onMessage(msg);
}

void LocalService::sSendMessage(const QString &replyTo, const LocalMessage &msg) {
    if (!mConnections.contains(replyTo)){
        qWarning() << "LocalService::onSendMessage failed, replyTo:" << replyTo << " does not exists.";
        return ;
    }

    LocalSocketPtr socket = mConnections.value(replyTo);
    Q_ASSERT(socket);
    Q_ASSERT(socket->isConnected());

    if (!socket->send(LocalMessage::toArray(msg))){
        qWarning() << "LocalService::onSendMessage failed, send:" << msg.toString() << " failed:" << socket->getErrorString();
        return ;
    }
}


}  // ~moon
