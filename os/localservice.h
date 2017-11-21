#ifndef PLATFORM_OS_LOCALSERVICE_H
#define PLATFORM_OS_LOCALSERVICE_H

#include <os/internal/internaldefine.h>
#include <os/localmessage.h>

#include <atomic>

#include <QObject>
#include <QString>
#include <QMap>

namespace moon {
class LocalServer;
class ServiceManager;
class LocalService : public QObject
{
    Q_OBJECT
    friend class ServiceManager;
public:
    LocalService();
    virtual ~LocalService();

    /**
     * Called by system when a message has be send to this LocalService object, uses should implement
     * this method to handle messages.
     * @param msg A LocalMessage object represents a request from clients.
     */
    virtual void onMessage(LocalMessage &msg) = 0;

    /**
     * Returns a name represents the service
     */
    virtual QString getName() const = 0;

    /**
     * Called by the system when the service has started, the LocalService can do it initialization
     * in this method, this system will call this method only once, do not call it directly.
     */
    virtual void onStart(){}

    /**
     * Called by the system to notify a service that is no longer used and is being removed. The LocalService should clean up
     * any resources(threads, file descriptors) it holds at this point. Upon return, there will no more calls into this
     * LocalService object and it efficiently dead. This system will call this method only once, do not call it directly.
     */
    virtual void onStop(){}

    /**
     * Called by the system when the service can not start. If this method
     */
    virtual void onStartFailed(const QString &error){Q_UNUSED(error);}

    /**
     * Called by the system when a client has connected to this LocalSevice object.
     * If you want to minitor the the new connected client you should reimplement this function.
     * @param name A QString object represents the connected client's name.
     */
    virtual void onNewConnection(const QString& name){Q_UNUSED(name);}

    /**
     * Called by the system when a client has disconnected from this LocalSevice object.
     */
    virtual void onDisconnected(const QString& name){Q_UNUSED(name);}

    /**
     * Returns how many clients has connected to this LocalService object currently.
     */
    virtual int getClientNums() const {return mConnections.size();}

    /**
     * Sends a message represented by a LocalMessage object to the clients specified by @replyTo.
     *
     */
    void reply(const QString &replyTo, const LocalMessage &msg){emit sendMessageSignal(replyTo, msg);}
private:
    virtual bool startService();
    virtual void stopService();
private slots:
    void sNewConnection(const LocalSocketPtr &conn);
    void sDisconnection(const QString &name);
    void sNewMessage(const QString name, const QByteArray &data);
    void sSendMessage(const QString &replyTo, const LocalMessage &msg);
signals:
    void sendMessageSignal(const QString& replyTo, const LocalMessage &msg);
protected:
    LocalServer *mLocalServer;
    QMap<QString, LocalSocketPtr> mConnections;

};


} // ~moon

#endif // PLATFORM_OS_LOCALSERVICE_H
