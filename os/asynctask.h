#ifndef PLATFORM_OS_ASYNCTASK_H
#define PLATFORM_OS_ASYNCTASK_H

#include <atomic>

#include <QObject>
#include <QVariant>

namespace moon {

class AsyncTask : public QObject
{
    Q_OBJECT
    friend class AsyncTaskExecutor;
    enum Status{PENDING = 10, RUNNING, FINISHED};
public:
    AsyncTask();

    bool isCancelled() const {return mCancelled;}

    bool cancel() {
        mCancelled = true;
        return true;
    }

    void execute();

    /**
     * Override this method to perform a computation on a background thread.
     */
    virtual QVariant doInBackground() = 0;

    /**
     * Runs on the main thread before #doInBackground();
     */
    virtual void onPreExecute() {}

    /**
     * Runs on the main thread after #doInBackground();
     */
    virtual void onPostExecute(const QVariant &result) {Q_UNUSED(result);}

    /**
     * Runs on the main thread after #cancle() is invoked and #doInBackground() has finished.
     */
    virtual void onCancelled() {}

    /**
     * Runs on the main thread after #publishProgress() is invoked.
     */
    virtual void onProgressUpdate(const QVariant &progress) {Q_UNUSED(progress);}

    /**
     * This method can be invoked from #doInBackground() to publish updates on the
     * main thread while the backgorund computation is still running. Each call to this method
     * will trigger the execution of #onProgressUpdate() on the main thread.
     */
    void publishProgess(const QVariant &progess) {emit postProgress(progess);}
signals:
    void postProgress(const QVariant &progess);
    void postResult(const QVariant &result);
private slots:
    void onHandleProgress(const QVariant &progess) {onProgressUpdate(progess);}
    void onFinish(const QVariant &result) {
        mState = Status::FINISHED;
        if (!mCancelled){
            onPostExecute(result);
        }else{
            onCancelled();
        }
        deleteLater();
    }

private:
    std::atomic<bool> mCancelled;
    std::atomic<int> mState;
};


}  // ~moon

#endif // PLATFORM_OS_ASYNCTASK_H
