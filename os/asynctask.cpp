#include <os/asynctask.h>
#include <os/asynctaskexecutor.h>
#include <QDebug>

namespace moon {

AsyncTask::AsyncTask() {
    mState = Status::PENDING;
    mCancelled = false;
    //connect(this, &AsyncTask::postProgress, [this](const QVariant &progess){onProgressUpdate(progess);});
    //connect(this, &AsyncTask::postResult, [this](const QVariant &result){finish(result);});
    connect(this, &AsyncTask::postProgress, this, &AsyncTask::onHandleProgress);
    connect(this, &AsyncTask::postResult, this, &AsyncTask::onFinish);
}

void AsyncTask::execute() {
    if (Status::PENDING != mState){
        qWarning() << "AsyncTask::execute failed, task not at pendding state, current state is:" << mState;
        return ;
    }
    mState = Status::RUNNING;
    onPreExecute();
    AsyncTaskExecutor::getInstance().execute(this);
}



}  // ~moon
