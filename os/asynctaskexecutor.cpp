#include <os/asynctaskexecutor.h>
#include <os/asynctask.h>

#include <QDebug>
#include <QRunnable>
#include <QThreadPool>

namespace moon {

class TaskRunnable : public QRunnable{
public:
    TaskRunnable(AsyncTask *task) : mTask(task) {}
    void run() Q_DECL_OVERRIDE{
        QVariant result = mTask->doInBackground();
        emit mTask->postResult(result);
    }
private:
    AsyncTask *mTask;
};

AsyncTaskExecutor::AsyncTaskExecutor() {
    mThreadPool = new QThreadPool();
    mThreadPool->setMaxThreadCount(5);
    mThreadPool->setExpiryTimeout(300 * 1000);
}

AsyncTaskExecutor::~AsyncTaskExecutor() {
    Q_ASSERT(NULL != mThreadPool);
    delete mThreadPool;
    mThreadPool = NULL;
}

void AsyncTaskExecutor::execute(AsyncTask *task) {
    if (NULL == task){
        qDebug() << "AsyncTaskExecutor::execute failed, argument task should not be NULL.";
        return ;
    }

    mThreadPool->start(new TaskRunnable(task));
}


}
