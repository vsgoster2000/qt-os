#include "clienttestdialog.h"
#include "ui_clienttestdialog.h"

#include <functional>
#include <os/localconnection.h>

#include <QDebug>
#include <QThread>

ClientTestDialog::ClientTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientTestDialog)
{
    ui->setupUi(this);
    connect(ui->connetService, &QPushButton::clicked, this, &ClientTestDialog::onConnectService);
    connect(ui->disconnectService, &QPushButton::clicked, this, &ClientTestDialog::onDisconnectService);
    connect(ui->sendData, &QPushButton::clicked, this, &ClientTestDialog::onSendData);
}

ClientTestDialog::~ClientTestDialog()
{
    delete ui;
}

void ClientTestDialog::onConnectService(){
    mConnection = LocalConnection::connectToServer("service.test");
    if (mConnection){
        mConnection->setOnDisconnectedListener([this](){
            showStatus("Connected has disconnected");
            qDebug() << "Connection:" << mConnection->getName() << " disconnected.";

        });
        mConnection->setOnNewMessageListener(std::bind(&ClientTestDialog::onMessage, this, std::placeholders::_1));
        //mConnection->setOnDataReceivedListener(std::bind(&ClientTestDialog::onReceivingData, this, std::placeholders::_1));
        showStatus("Connected has established");


        return ;
    }else{
        showStatus("Unable to connect service");
    }
}

void ClientTestDialog::onDisconnectService(){
    if (mConnection){
        mConnection->close();
        mConnection.reset();
        showStatus("Connection has closed");
    }
}

void ClientTestDialog::onSendData(){
    if (mConnection){
        LocalMessage msg;
        msg.what = 11;
        msg.arg1 = 12;
        msg.arg2 = 13;
        msg.str = ui->inputData->text();
        if (!mConnection->send(msg)){
            qDebug() << "Send data failed:" << mConnection->getErrorString();
            return ;
        }
    }
}

void ClientTestDialog::onReceivingData(const QByteArray &data) {
    showRecvData(data);
}

void ClientTestDialog::onMessage(const LocalMessage &msg){
    showRecvData(msg.toArray());
}

void ClientTestDialog::showStatus(const QString &text) {
    ui->showStatus->setText(text);
}

void ClientTestDialog::showStatus(const char *format) {
    showStatus(QString(format));
    //    Q_ASSERT(NULL != format);

    //    va_list ap;
    //    va_start(ap, format);
    //    QString text = QString::vasprintf(format, ap);
    //    va_end(ap);

    //    ui->showStatus->setText(text);
}

void ClientTestDialog::showRecvData(const QByteArray &data) {
    QString originText = ui->showRecvData->toPlainText();
    if (originText.isEmpty()){
        originText.append("recv:").append(data);
    }else{
        originText.append("\r\n");
        originText.append("recv:").append(data);
    }
    ui->showRecvData->setText(originText);
}
