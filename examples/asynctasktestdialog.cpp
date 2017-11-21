#include "asynctasktestdialog.h"
#include "ui_asynctasktestdialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QThread>

class TestAsyncTask : public AsyncTask
{
public:
    TestAsyncTask() {qDebug() << "TestAsyncTask#constructor";}
    ~TestAsyncTask() {qDebug() << "TestAsyncTask#deconstructor";}

    /**
     * Override this method to perform a computation on a background thread.
     */
    virtual QVariant doInBackground(){
        qDebug() << "TestAsyncTask#doInBackground threadId:" << QThread::currentThread();
        QThread::sleep(1);

        QVariant v(123);
        return v;
    }

    /**
     * Runs on the main thread before #doInBackground();
     */
    virtual void onPreExecute() {
        qDebug() << "TestAsyncTask#onPreExecute threadId:" << QThread::currentThread();
    }

    /**
     * Runs on the main thread after #doInBackground();
     */
    virtual void onPostExecute(const QVariant &result) {
        qDebug() << "TestAsyncTask#onPostExecute threadId:" << QThread::currentThread() << ", result:" << result.toInt();
    }

    /**
     * Runs on the main thread after #cancle() is invoked and #doInBackground() has finished.
     */
    virtual void onCancelled() {
        qDebug() << "TestAsyncTask#onCancelled threadId:" << QThread::currentThread();
    }

    /**
     * Runs on the main thread after #publishProgress() is invoked.
     */
    virtual void onProgressUpdate(const QVariant &progress) {
        qDebug() << "TestAsyncTask#onProgressUpdate threadId:" << QThread::currentThread() << ", progress:" << progress.toInt();
    }
};

class LoadProgressAsyncTask : public AsyncTask
{
public:
    LoadProgressAsyncTask(QProgressBar *progressBar) : mProgressBar(progressBar) {
        qDebug() << "LoadProgressAsyncTask#constructor";}
    ~LoadProgressAsyncTask() {qDebug() << "LoadProgressAsyncTask#deconstructor";}

    /**
     * Override this method to perform a computation on a background thread.
     */
    virtual QVariant doInBackground(){
        for (int i = 0; i <= 100; i+=10){
            QThread::msleep(500);
            QVariant progess(i);
            publishProgess(progess);
            if (isCancelled()){
                return QVariant(1);
            }
        }

        return QVariant(0);
    }

    virtual void onPreExecute() {
        qDebug() << "LoadProgressAsyncTask#onPreExecute threadId:" << QThread::currentThread();
    }

    virtual void onPostExecute(const QVariant &result) {
        qDebug() << "LoadProgressAsyncTask#onPostExecute threadId:" << QThread::currentThread() << ", result:" << result.toInt();
        QMessageBox::about(NULL, "Hint", "Success");
    }

    virtual void onCancelled() {
        qDebug() << "LoadProgressAsyncTask#onCancelled threadId:" << QThread::currentThread();
        QMessageBox::about(NULL, "Hint", "Cancelled");
    }

    virtual void onProgressUpdate(const QVariant &progress) {
        mProgressBar->setValue(progress.toInt());
        //qDebug() << "onProgressUpdate threadId:" << QThread::currentThread() << ", progress:" << progress.toInt();
    }
private:
    QProgressBar *mProgressBar;
};

AsyncTaskTestDialog::AsyncTaskTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AsyncTaskTestDialog)
{
    mAsyncTask = NULL;
    ui->setupUi(this);
    connect(ui->testAsyncTask1, &QPushButton::clicked, this, &AsyncTaskTestDialog::testAsyncTask1);
    connect(ui->startLoadProgress, &QPushButton::clicked, this, &AsyncTaskTestDialog::loadProgress);
    connect(ui->cancelLoadProgress, &QPushButton::clicked, this, &AsyncTaskTestDialog::onCancelLoadProgress);
}

AsyncTaskTestDialog::~AsyncTaskTestDialog()
{
    delete ui;
}

void AsyncTaskTestDialog::testAsyncTask1() {
    qDebug() << "AsyncTaskTestDialog#testAsyncTask1 threadId:" << QThread::currentThread();
    TestAsyncTask *task = new TestAsyncTask();
    task->execute();
}

void AsyncTaskTestDialog::loadProgress() {
    qDebug() << "AsyncTaskTestDialog#loadProgress threadId:" << QThread::currentThread();
    if (NULL == mAsyncTask){
        mAsyncTask = new LoadProgressAsyncTask(ui->progressBar);
        mAsyncTask->execute();
    }else{
        qDebug() << "AsyncTaskTestDialog#loadProgress do nothing";
   }
}

void AsyncTaskTestDialog::onCancelLoadProgress(){
    qDebug() << "AsyncTaskTestDialog#onCancelLoadProgress threadId:" << QThread::currentThread();
    if (NULL != mAsyncTask){
        mAsyncTask->cancel();
    }else{
         qDebug() << "AsyncTaskTestDialog#onCancelLoadProgress NULL object";
    }
}



