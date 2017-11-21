#include "handlertestdialog.h"
#include "ui_handlertestdialog.h"

#include <os/handler.h>
#include <functional>
#include <QDebug>

using namespace moon;

void handleMessage(const Message &msg){
    qDebug() << "handleMessage, ThreadId:" << QThread::currentThread();
    qDebug("msg.what[%d], msg.arg1[%d], msg.arg2[%d]", msg.what(), msg.arg1(), msg.arg2());
}


HandlertestDialog::HandlertestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HandlertestDialog)
{
    ui->setupUi(this);
    connect(ui->testHandler1, &QPushButton::clicked, this, &HandlertestDialog::onTestHandler1);
    connect(ui->testHandler2, &QPushButton::clicked, this, &HandlertestDialog::onTestHandler2);
    connect(ui->testHandler3, &QPushButton::clicked, this, &HandlertestDialog::onTestHandler3);

    mThread = new QThread();
    mThread->start();
}

HandlertestDialog::~HandlertestDialog()
{
    delete ui;
}

void HandlertestDialog::onTestHandler1(){
    qDebug() << "HandlertestDialog::onTestHandler1, ThreadId:" << QThread::currentThread();
    HandlerPtr handler = Handler::create();
    Message msg = Message::obtain(1, 2, 3);
    handler->setMessageHandler(std::bind(handleMessage, std::placeholders::_1));
    handler->sendMessage(msg);
}

void HandlertestDialog::onTestHandler2(){
    qDebug() << "HandlertestDialog::onTestHandler2, ThreadId:" << QThread::currentThread();

    mHandler = Handler::create(mThread);
    Message msg = Message::obtain(11, 12, 13);
    mHandler->setMessageHandler(std::bind(handleMessage, std::placeholders::_1));
    mHandler->sendMessage(msg);
}

void HandlertestDialog::onTestHandler3(){
    qDebug() << "HandlertestDialog::onTestHandler3, ThreadId:" << QThread::currentThread();

    mHandler = Handler::create(mThread);
    QString text = "PostText";
    mHandler->postRunnable(std::bind(&HandlertestDialog::executeRunnable, this, text));
}

void HandlertestDialog::executeRunnable(const QString &text){
    qDebug() << "HandlertestDialog#executeRunnable, text:" << text << ", ThreadId:" << QThread::currentThread();
}
