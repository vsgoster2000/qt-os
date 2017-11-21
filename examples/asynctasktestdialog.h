#ifndef ASYNCTASKTESTDIALOG_H
#define ASYNCTASKTESTDIALOG_H

#include <os/asynctask.h>

#include <QDialog>

using namespace moon;

namespace Ui {
class AsyncTaskTestDialog;
}

class AsyncTaskTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AsyncTaskTestDialog(QWidget *parent = 0);
    ~AsyncTaskTestDialog();
private slots:
    void testAsyncTask1();

    void loadProgress();

    void onCancelLoadProgress();
private:
    Ui::AsyncTaskTestDialog *ui;
    AsyncTask *mAsyncTask;
};

#endif // ASYNCTASKTESTDIALOG_H
