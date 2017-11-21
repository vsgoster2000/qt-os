#include <os/internal/localsocket.h>
#include <os/internal/localsocketconnector.h>

#include <QLocalSocket>
#include <QMutexLocker>

namespace moon{

static unsigned long toMillis(unsigned long usec){
    return usec / 1000;
}

LocalSocket::LocalSocket(const QString &name, QLocalSocket *localSocket) : mName(name), mLocalSocket(localSocket){
    Q_ASSERT(!mName.isEmpty());
    Q_ASSERT(NULL != mLocalSocket);
    mConnected = true;
    connect(mLocalSocket, &QLocalSocket::disconnected, this, &LocalSocket::onDisconnected);
}

LocalSocket::~LocalSocket(){
    Q_ASSERT(NULL != mLocalSocket);
    close();
    delete mLocalSocket;
    mLocalSocket = NULL;
}

bool LocalSocket::send(const QByteArray &data){
    Q_ASSERT(!data.isEmpty());
    return send(data, 0, true);
}

bool LocalSocket::send(const QByteArray &data, unsigned long timeoutUsec) {
    Q_ASSERT(!data.isEmpty());
    return send(data, timeoutUsec, true);
}

QByteArray LocalSocket::recv(unsigned long timeoutUsec){
    if (!mConnected){
        setError("LocalSocket::recv failed, connection has already closed.");
        return false;
    }

    Q_ASSERT(NULL != mLocalSocket);
    if (!mLocalSocket->waitForReadyRead(toMillis(timeoutUsec))){
        setError("LocalSocket::recv failed, waitForReadyRead returns false:").append(mLocalSocket->errorString());
        return "";
    }

    return mLocalSocket->readAll();
}

void LocalSocket::close() {
    if (!mConnected){
        return ;
    }

    mLock.lock();
    if (mConnected){
        mConnected = false;
        mLock.unlock();

        disconnect(mLocalSocket, &QLocalSocket::disconnected, this, &LocalSocket::onDisconnected);
        mLocalSocket->abort();
    }else{
        mLock.unlock();
    }
}

bool LocalSocket::isConnected() const{
    return mConnected;
}

void LocalSocket::setOnDataReceivedListener(const OnDataReceivedListener &listener){
    mDataReceivedListener = listener;
    if (mDataReceivedListener){
        connect(mLocalSocket, &QLocalSocket::readyRead, this, &LocalSocket::onReadyRead);
    }else{
        disconnect(mLocalSocket, &QLocalSocket::readyRead, this, &LocalSocket::onReadyRead);
    }
}

void LocalSocket::onReadyRead() {
    if (mConnected){
        mDataReceivedListener(mLocalSocket->readAll());
    }
}

void LocalSocket::onDisconnected() {
    if (!mConnected){
        return ;
    }

    mLock.lock();
    if (mConnected){
        mConnected = false;
        mLock.unlock();

        if (mDisconnectedListener) {
            mDisconnectedListener();
        }
    }else{
        mLock.unlock();
    }
}

bool LocalSocket::send(const QByteArray &data, unsigned long timeoutUsec, bool blocked) {
    if (!mConnected){
        setError("LocalSocket::send failed, connection has already closed.");
        return false;
    }

    Q_ASSERT(NULL != mLocalSocket);
    int iRet = mLocalSocket->write(data);
    if (iRet < 0){
        setError("LocalSocket::send failed, write to connection occurs an error :").append(mLocalSocket->errorString());;
        return false;
    }

    if (!blocked){
        return true;
    }

    // use blocking way to write data, block this thread until the data really writed.
    if (mLocalSocket->waitForBytesWritten(toMillis(timeoutUsec))){
        return true;
    }

    setError("LocalConnection::send failed, waitForBytesWritten returns false:").append(mLocalSocket->errorString());
    return false;
}

QString& LocalSocket::setError(const char *format, ...) {
    if (NULL == format){
        return mErrorString;
    }

    va_list ap;
    va_start(ap, format);
    mErrorString = QString::vasprintf(format, ap);
    va_end(ap);
    return mErrorString;
}


}  // ~moon
