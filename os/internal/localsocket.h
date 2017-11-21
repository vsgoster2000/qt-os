#ifndef PLATFORM_OS_INTERNAL_LOCALSOCKET_H
#define PLATFORM_OS_INTERNAL_LOCALSOCKET_H

#include <os/internal/internaldefine.h>

#include <atomic>
#include <QObject>
#include <QMutex>

QT_BEGIN_NAMESPACE
class QLocalSocket;
QT_END_NAMESPACE

namespace moon {

class LocalSocket : public QObject
{
    Q_OBJECT
public:
    LocalSocket(const QString &name, QLocalSocket *localSocket);

    ~LocalSocket();

    /**
     * @brief Use @name and @localSocket to create a valid LocalSocketPtr object.
     * if @name is empty or @localSocket==NULL, returns an empty LocalSocketPtr object.
     *
     * @example
     * LocalSocketPtr socketPtr = LocalSocket::create("name", localSocket);
     * if (socketPtr){
     *     socketPtr is a valid object.
     * }else{
     *     socketPtr is am empty object.
     * }
     */
    static LocalSocketPtr create(const QString &name, QLocalSocket *localSocket){
        if ( (name.isEmpty()) || (NULL == localSocket) ){
            return LocalSocketPtr();
        }

        return LocalSocketPtr(new LocalSocket(name, localSocket));
    }

    bool send(const QString &data) {return send(data.toLocal8Bit());}
    bool send(const QByteArray &data);
    bool send(const QByteArray &data, unsigned long timeoutUsec);

    QByteArray recv(unsigned long timeoutUsec);

    void close();

    bool isConnected() const;

    const QString& getName() const {return mName;}

    const QString& getErrorString() const {return mErrorString;}

    void setOnDataReceivedListener(const OnDataReceivedListener &listener);

    void setOnDisconnectedListener(const OnDisconnectedListener &listener) {mDisconnectedListener = listener;}

private slots:
    void onReadyRead();
    void onDisconnected();
private:
    bool send(const QByteArray &data, unsigned long timeoutUsec, bool blocked);

    QString& setError(const QString &error){mErrorString = error; return mErrorString;}
    QString& setError(const char *format, ...);
private:
    bool mConnected;
    const QString mName;
    QLocalSocket *mLocalSocket;
    QMutex mLock;
    QString mErrorString;
    OnDataReceivedListener mDataReceivedListener;
    OnDisconnectedListener mDisconnectedListener;
};


}  // ~moon
#endif // PLATFORM_OS_INTERNAL_LOCALSOCKET_H
