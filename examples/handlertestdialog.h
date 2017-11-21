#ifndef HANDLERTESTDIALOG_H
#define HANDLERTESTDIALOG_H

#include <os/handler.h>
#include <QDialog>
#include <QThread>

using namespace moon;

namespace Ui {
class HandlertestDialog;
}

class HandlertestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HandlertestDialog(QWidget *parent = 0);
    ~HandlertestDialog();

private slots:
    // Test handler in the main thread
    void onTestHandler1();

    // Test handler in a child thread
    void onTestHandler2();

    // Post runnable object to handler
    void onTestHandler3();

    void executeRunnable(const QString &text);
private:
    Ui::HandlertestDialog *ui;
    QThread *mThread;
    HandlerPtr mHandler;
};

#endif // HANDLERTESTDIALOG_H
