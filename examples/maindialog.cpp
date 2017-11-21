#include "maindialog.h"
#include "ui_maindialog.h"
#include "asynctasktestdialog.h"
#include "handlertestdialog.h"
#include "servicetestdialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    connect(ui->handlerTest, &QPushButton::clicked, [this](){
        HandlertestDialog *d = new HandlertestDialog(this);
        d->show();
    });

    connect(ui->serviceTest, &QPushButton::clicked, [this](){
        ServiceTestDialog *d = new ServiceTestDialog(this);
        d->show();
    });

    connect(ui->asyncTaskTest, &QPushButton::clicked, [this](){
        AsyncTaskTestDialog *d = new AsyncTaskTestDialog(this);
        d->show();
    });
}

MainDialog::~MainDialog()
{
    delete ui;
}
