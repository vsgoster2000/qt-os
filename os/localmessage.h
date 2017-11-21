#ifndef PLATFORM_OS_LOCALMESSAGE_H
#define PLATFORM_OS_LOCALMESSAGE_H

#include <atomic>

#include <QString>

namespace moon{

class LocalMessage
{
public:
    LocalMessage() : okey(false), what(0), arg1(0), arg2(0), str(){ }

    static LocalMessage create(const QByteArray &data) {
        return create(QString(data));
    }

    static LocalMessage create(const QString &data);

    static QString toString(const LocalMessage &message);

    static QByteArray toArray(const LocalMessage &message) {return toString(message).toLocal8Bit();}
public:
    QString toString() const {
        return QString("what=%1&arg1=%2&arg2=%3&str=%4").arg(what).arg(arg1).arg(arg2).arg(str);
    }

    QByteArray toArray() const{
       return toString().toLocal8Bit();
    }

public:
    bool okey;
    int what;
    int arg1;
    int arg2;
    QString str;
    QString replyTo;
private:
    static std::atomic<bool> sRegisterd;
    static void registerThis();
};


}  // ~moon
#endif // PLATFORM_OS_LOCALMESSAGE_H
