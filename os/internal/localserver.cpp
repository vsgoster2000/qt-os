#include <os/internal/localserver.h>
#include <os/internal/localsocket.h>

#include <QLocalSocket>
#include <QLocalServer>
#include <QMapIterator>

namespace moon {

LocalServer::LocalServer(const QString &serverName) : mServerName(serverName){
    mStarted = false;
    mConnectionNo = 0;
    mLocalServer = new QLocalServer();
}

LocalServer::~LocalServer(){
    Q_ASSERT(NULL != mLocalServer);

    delete mLocalServer;
    mLocalServer = NULL;
}

bool LocalServer::start(){
    if (mStarted){
        return false;
    }
    Q_ASSERT(NULL != mLocalServer);
    if (!mLocalServer->listen(mServerName)){
        qDebug() << "LocalServer::start failed, " << mLocalServer->errorString();
        return false;
    }

    mStarted = true;
    QObject::connect(mLocalServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    emit started();

    return true;
}

void LocalServer::stop(){
    if (!mStarted){
        return ;
    }

    Q_ASSERT(NULL != mLocalServer);
    Q_ASSERT(mLocalServer->isListening());

    if (mStarted){
        mStarted = false;
        mLocalServer->close();
        emit stopped();
    }
}

QString LocalServer::errorString() const {
    return mLocalServer->errorString();
}

void LocalServer::onNewConnection(){
    QLocalSocket *socket = mLocalServer->nextPendingConnection();
    Q_ASSERT(NULL != socket);

    const QString connName = QString("%1-service-%2").arg(mServerName).arg(++mConnectionNo);

    LocalSocketPtr conn = LocalSocket::create(connName, socket);
    Q_ASSERT(conn);

    if (mNewConnectionListener){
        mNewConnectionListener(conn);
    }
}


}  // ~moon
