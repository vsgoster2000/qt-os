#ifndef PLATFORM_OS_INTERNAL_LOCALSERVER_H
#define PLATFORM_OS_INTERNAL_LOCALSERVER_H

#include <os/internal/internaldefine.h>

#include <atomic>

#include <QObject>
#include <QString>


QT_BEGIN_NAMESPACE
class QLocalServer;
QT_END_NAMESPACE

namespace moon{
class LocalServer : public QObject
{
    Q_OBJECT
public:
    LocalServer(const QString &serverName);
    virtual ~LocalServer();

    bool start();

    void stop();

    void setOnNewConnectionListener(const OnNewConnectionListener &listener) {mNewConnectionListener = listener;}

    QString errorString() const;
private slots:
    void onNewConnection();
signals:
    void started();
    void stopped();
private:
    bool mStarted;
    std::atomic<unsigned long> mConnectionNo;
    const QString mServerName;
    QLocalServer *mLocalServer;
    OnNewConnectionListener mNewConnectionListener;
};

}  // ~moon

#endif // PLATFORM_OS_INTERNAL_LOCALSERVER_H
