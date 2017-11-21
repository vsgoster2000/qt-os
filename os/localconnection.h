#ifndef PLATFORM_OS_LOCALCONNECTION_H
#define PLATFORM_OS_LOCALCONNECTION_H

#include <os/internal/internaldefine.h>
#include <os/internal/localsocket.h>
#include <os/localconnectiondefine.h>
#include <os/localmessage.h>

#include<functional>

#include <QByteArray>

namespace moon{
/**
 * @brief Defines a interface for LocalConnection to call when it received some new data.
 */
typedef std::function<void (const LocalMessage &data)> OnNewMessageListener;

class LocalConnection : QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(LocalConnection)
    enum {kSendAndRecvTimeout = 1000000};
public:
    virtual ~LocalConnection();

    /**
      * @brief Connect to a Server specified by @serverName, this method will block the calling thread,
      * until connected to the server or an error occurs during connecting, this method at most block @timeoutMillis milliseconds.
      *
      * @param serverName a QString object represents the name of the server going to connect.
      * @param timeoutMillis a unsigned long number, the maximum time this method would block.
      *
      * @return Returns a valid LocalConnectionPtr object on success, if on failure returns an empty LocalConnectionPtr object.
      */
    static LocalConnectionPtr connectToServer(const QString &serverName, unsigned long timeoutMillis = 2000);

    /**
     * Returns a valid LocalConnectionPtr object on success, if on failure returns an empty LocalConnectionPtr object.
     */
    static LocalConnectionPtr create(LocalSocketPtr socket){
        if (socket){
            return LocalConnectionPtr(new LocalConnection(socket));
        }
        return LocalConnectionPtr();
    }

    /**
     * Returns a valid LocalConnectionPtr object on success, if on failure returns an empty LocalConnectionPtr object.
     * If @name is empty or @socket==NULL, returns an empty LocalConnectionPtr object.
     */
    static LocalConnectionPtr create(const QString &name, QLocalSocket *socket){
        return create(LocalSocket::create(name, socket));
    }

    virtual bool send(const LocalMessage &msg) {
        Q_ASSERT(mLocalSocket);
        if (mLocalSocket->isConnected()){
            return mLocalSocket->send(LocalMessage::toArray(msg), kSendAndRecvTimeout);
        }
        return false;
    }

    virtual bool send(const LocalMessage &msg, unsigned long timeoutUsec) {
        Q_ASSERT(mLocalSocket);
        if (mLocalSocket->isConnected()){
            return mLocalSocket->send(LocalMessage::toArray(msg), timeoutUsec);
        }
        return false;
    }

    virtual LocalMessage recv() {
        return recv(kSendAndRecvTimeout);
    }

    virtual LocalMessage recv(unsigned long timeoutUsec) {
        Q_ASSERT(mLocalSocket);
        if (mLocalSocket->isConnected()){
            return LocalMessage::create(mLocalSocket->recv(timeoutUsec));
        }

        return LocalMessage();
    }

    virtual void close() {
        Q_ASSERT(mLocalSocket);
        mLocalSocket->close();
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

    void setOnNewMessageListener(const OnNewMessageListener &listener) {
        Q_ASSERT(mLocalSocket);
        mOnNewMessageListener = listener;
    }

    void setOnDisconnectedListener(const OnDisconnectedListener &listener) {
        Q_ASSERT(mLocalSocket);
        mLocalSocket->setOnDisconnectedListener(listener);
    }

private:
    LocalConnection(LocalSocketPtr localSocket);
private slots:
    void onData(const QByteArray &data);
private:
    LocalSocketPtr mLocalSocket;
    OnNewMessageListener mOnNewMessageListener;
};



}  //~ moon
#endif // PLATFORM_OS_LOCALCONNECTION_H
