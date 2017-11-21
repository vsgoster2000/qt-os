#include <os/message.h>

namespace moon{

Message Message::obtain(int what){
    return Message(what, 0, 0, NULL, NULL, NULL);
}

Message Message::obtain(int what, int arg1){
    return Message(what, arg1, 0, NULL, NULL, NULL);
}

Message Message::obtain(int what, int arg1, int arg2){
    return Message(what, arg1, arg2, NULL, NULL, NULL);
}

Message Message::obtain(int what, int arg1, int arg2, const QString& str){
    return Message(what, arg1, arg2, str, NULL, NULL);
}

Message Message::obtain(int what, int arg1, int arg2, const QVariant& obj){
    return Message(what, arg1, arg2, NULL, NULL, obj);
}

Message Message::obtain(int what, int arg1, int arg2, const QString& str, const QVariant& obj){
    return Message(what, arg1, arg2, str, NULL,  obj);
}

Message Message::obtain(int what, int arg1, int arg2, const QString& str, const Runnable& r, const QVariant& obj){
    return Message(what, arg1, arg2, str, r,  obj);
}

Message Message::obtain(const QString& str){
    return Message(0, 0, 0, str, NULL, NULL);
}

Message Message::obtain(const Runnable& r){
    return Message(0, 0, 0, NULL, r, NULL);
}

Message::Message() : mWhat(0), mArg1(0), mArg2(0), mStr(), mObj(NULL){
    registerThis();
}

Message::Message(int what, int arg1, int arg2, const QString& str, const Runnable& r, const QVariant& obj) :
    mWhat(what), mArg1(arg1), mArg2(arg2), mStr(str), mRunnable(r), mObj(obj)
{
    registerThis();
}

Message::Message(const Message& other){
    mWhat = other.mWhat;
    mArg1 = other.mArg1;
    mArg2 = other.mArg2;
    mStr = other.mStr;
    mObj = other.mObj;
    mRunnable = other.mRunnable;
    registerThis();
}

Message& Message::operator=(const Message& other){
    mWhat = other.mWhat;
    mArg1 = other.mArg1;
    mArg2 = other.mArg2;
    mStr = other.mStr;
    mObj = other.mObj;
    mRunnable = other.mRunnable;

    return *this;
}

Message::~Message()
{
}

std::atomic<bool> Message::sRegisterd = false;
void Message::registerThis(){
    if (!sRegisterd){
        sRegisterd = true;
        qRegisterMetaType<Message>("Message");
    }
}


} // ~moon
