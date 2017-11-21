#include "servicetestdialog.h"
#include "ui_servicetestdialog.h"
#include "clienttestdialog.h"
#include <os/servicemanager.h>

ServiceTestDialog::ServiceTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServiceTestDialog)
{
    mService = NULL;
    ui->setupUi(this);

    connect(ui->startCient, &QPushButton::clicked, [this](){
        ClientTestDialog *d = new ClientTestDialog(this);
        d->show();
    });

    connect(ui->startService, &QPushButton::clicked, this, &ServiceTestDialog::onStartService);
    connect(ui->stopService, &QPushButton::clicked, this, &ServiceTestDialog::onStopService);
    connect(ui->sendData, &QPushButton::clicked, [this](){
        if (NULL != mService){
            mService->sendData(ui->inputData->text().toLocal8Bit());
        }
    });
}

ServiceTestDialog::~ServiceTestDialog(){
    delete ui;
}

void ServiceTestDialog::onStartService() {
    if (NULL == mService){
        mService = new ChattingService();
        mService->setTextEdit(ui->showRecvData).setStatusEdit(ui->showStatus);
    }

    ServiceManager::getInstance().startService(mService);
}

void ServiceTestDialog::onStopService() {
    ServiceManager::getInstance().stopService(mService);
}

void ServiceTestDialog::showStatus(const QString &text) {
    ui->showStatus->setText(text);
}

void ServiceTestDialog::showStatus(const char *format) {
    showStatus(QString(format));
    //    Q_ASSERT(NULL != format);
    //    va_list ap;
    //    va_start(ap, format);
    //    QString text = QString::vasprintf(format, ap);
    //    va_end(ap);

    //    ui->showStatus->setText(text);
}
