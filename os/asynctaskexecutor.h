#ifndef PLATFORM_OS_ASYNCTASKEXECUTOR_H
#define PLATFORM_OS_ASYNCTASKEXECUTOR_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QThreadPool;
QT_END_NAMESPACE

namespace moon {
class AsyncTask;

class AsyncTaskExecutor : QObject
{
    Q_OBJECT
private:
    AsyncTaskExecutor();
public:
    ~AsyncTaskExecutor();

    static AsyncTaskExecutor& getInstance() {
        static AsyncTaskExecutor instance;
        return instance;
    }

    void execute(AsyncTask *task);

private:
    QThreadPool *mThreadPool;
};


} // ~moon
#endif // PLATFORM_OS_ASYNCTASKEXECUTOR_H
