#ifndef CHATTINGSERViCE_H
#define CHATTINGSERViCE_H

#include <os/LocalService.h>

#include <functional>

#include <QDebug>
#include <QLineEdit>
#include <QTextEdit>
#include <QMap>

using namespace moon;

class ChattingService : public LocalService
{
public:
    ChattingService() : LocalService() {}

    ChattingService& setTextEdit(QTextEdit *textEdit){
        mShowRecvData = textEdit;
        return *this;
    }

    ChattingService& setStatusEdit(QLineEdit *showStatus){
        mShowStatus = showStatus;
        return *this;
    }

    virtual void onMessage(LocalMessage &msg) {
        mMessage = msg;
        showReceivingData(msg.toString().toLocal8Bit(), "recv:", "\r\n");
    }

    virtual QString getName() const {
        return "service.test";
    }

    virtual void onStart(){
        qDebug() << "ChattingService#onStart";
    }

    virtual void onStop(){
        qDebug() << "ChattingService#onStop";
    }

    virtual void onNewConnection(const QString& name){
        qDebug() << "ChattingService#onNewConnection, name:" << name;
        QString status = QString("Current connection nums: %1").arg(getClientNums());
        mShowStatus->setText(status);
    }

    virtual void onDisconnected(const QString& name){
        qDebug() << "ChattingService#onConnectionDisconnected, name:" << name;
        QString status = QString("Current connection nums: %1").arg(getClientNums());
        mShowStatus->setText(status);
    }

    void sendData(const QByteArray &data){
        LocalMessage msg;
        msg.what = 101;
        msg.arg1 = 102;
        msg.arg2 = 103;
        msg.str = QString(data);
        reply(mMessage.replyTo, msg);

        showReceivingData(data, "send:", "\r\n");
    }



    virtual QString getServiceName(){
        return "server.test";
    }

private slots:
    void showReceivingData(const QByteArray &data, const char *mark, const char *append){
        QString originText = mShowRecvData->toPlainText();
        if (originText.isEmpty()){
            originText.append(mark).append(data);
        }else{
            originText.append(append);
            originText.append(mark).append(data);
        }
        mShowRecvData->setText(originText);
    }

private:
    LocalMessage mMessage;
    QTextEdit *mShowRecvData;
    QLineEdit *mShowStatus;
};

#endif // CHATTINGSERViCE_H
