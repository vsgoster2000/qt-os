#ifndef SERVICETESTDIALOG_H
#define SERVICETESTDIALOG_H

#include "chattingservice.h"

#include <QDialog>

using namespace moon;

namespace Ui {
class ServiceTestDialog;
}

class ServiceTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceTestDialog(QWidget *parent = 0);
    ~ServiceTestDialog();
private slots:
    void onStartService();
    void onStopService();

    void showStatus(const QString &text);
    void showStatus(const char *format);
private:
    Ui::ServiceTestDialog *ui;
    ChattingService *mService;
};

#endif // SERVICETESTDIALOG_H
