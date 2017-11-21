#include <os/handler.h>
#include <os/message.h>

#include <QDebug>
#include <QThread>

namespace moon{

HandlerPtr Handler::create(QThread *thread){
    if (NULL == thread){
        return HandlerPtr(new Handler());
    }

    Handler *handler = new Handler();
    if (QThread::currentThread() != thread){
        handler->moveToThread(thread);
    }

    return HandlerPtr(handler);
}

Handler::Handler(){
    mMessageHandler = NULL;
    connect(this, &Handler::submitMessage, this, &Handler::handleMessage);
}

Handler::~Handler(){
}

void Handler::sendMessage(const Message& msg){
    emit submitMessage(msg);
}

void Handler::postRunnable(const Runnable &runnable){
    emit submitMessage(Message::obtain(runnable));
}

void Handler::handleMessage(const Message& msg){
    if (NULL != msg.runnable()){
        msg.runnable()();
        return ;
    }

    if (NULL != mMessageHandler){
        mMessageHandler(msg);
    }else{
        qDebug() << "Using default behavior to handle message, message what:" << msg.what();
    }
}


}  // moon
