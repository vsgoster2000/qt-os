#ifndef PLATFORM_OS_MESSAGE_H
#define PLATFORM_OS_MESSAGE_H

#include <os/handlerdefine.h>

#include <atomic>

#include <QString>
#include <QVariant>

namespace moon {

/**
 * @brief Defining a  message containing a description and arbitrary data object
 * that can be send to a Handler.
 * This object contains two int fields, a QString object, and a QVariant object.
 *
 */
class Message
{
public:
    static Message obtain(int what);

    static Message obtain(int what, int arg1);

    static Message obtain(int what, int arg1, int arg2);

    static Message obtain(int what, int arg1, int arg2, const QString& str);

    static Message obtain(int what, int arg1, int arg2, const QVariant& obj);

    static Message obtain(int what, int arg1, int arg2, const QString& str, const QVariant& obj);

    static Message obtain(int what, int arg1, int arg2, const QString& str, const Runnable& r, const QVariant& obj);

    static Message obtain(const QString& str);

    static Message obtain(const Runnable& r);
public:
    Message();
    Message(int what, int arg1, int arg2, const QString& str, const Runnable& r, const QVariant& obj);
    Message(const Message& other);
    Message& operator=(const Message& other);
    ~Message();

    int what() const{return mWhat;}

    int arg1() const{return mArg1;}

    int arg2() const{return mArg2;}

    QString str() const{return mStr;}

    Runnable runnable() const{return mRunnable;}

    QVariant obj() const{
        return mObj;
    }
private:
    static void registerThis();

private:
    int mWhat;
    int mArg1;
    int mArg2;
    QString mStr;
    Runnable mRunnable;
    QVariant mObj;
    static std::atomic<bool> sRegisterd;
};

Q_DECLARE_METATYPE(Message)

}  // ~moon

#endif // PLATFORM_OS_MESSAGE_H
