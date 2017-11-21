#ifndef PLATFORM_OS_HANDLER_H
#define PLATFORM_OS_HANDLER_H

#include <os/handlerdefine.h>
#include <os/message.h>


#include <QObject>

QT_BEGIN_NAMESPACE
class QThread;
QT_END_NAMESPACE

namespace moon{

/**
 * @brief A Handler allows your to send a Message and Runnable objects associated with a thread.
 * Each Handler instance is associated with a single thread. Using Handler is very convenient for thread communication.
 *
 * A Handler object use an MessageHandler object as its Message handler,
 * a handler will post messages to the thread this handler object associated with, when the thread received a message,
 * the thread will use the MessageHandler object to handle the message, if the MessageHandler object is NULL, then do nothing.
 *
 * A Handler object can post an Runnbale object to the thread this handler object associated with, and the Runnable object
 * will be executed in the thread.
 */
class Handler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Handler)
public:
    static HandlerPtr create(QThread *thread = NULL);
private:
    Handler();

public:
    ~Handler();

    /**
     * @brief Set a MessageHandler object to handle messages. If your don't set a MessageHandler object,
     * Handler will use the default behavior to handle messages which is simply print the message.
     */
    void setMessageHandler(const MessageHandler& handler){mMessageHandler = handler;}

    /**
     * @brief Send a Message object to the thread this object associated with
     */
    void sendMessage(const Message& msg);

    /**
     * @brief Post an Runnable object to the thread this object associated with
     */
    void postRunnable(const Runnable& runnable);
signals:
    void submitMessage(const Message& msg);
private slots:
    void handleMessage(const Message& msg);
private:
    MessageHandler mMessageHandler;
};


}  // moon
#endif // PLATFORM_OS_HANDLER_H
