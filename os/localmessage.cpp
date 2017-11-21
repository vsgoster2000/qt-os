#include <os/localmessage.h>

#include <QMetaType>

namespace moon{

static int toInt(const QString &data, int start, int count){
    return data.mid(start, count).toInt();
}

static QString intToString(int num, int length){
    QString numStr = QString::number(num);
    if (numStr.size() == length){
        return numStr;
    }else if (numStr.size() > length){
        return numStr.mid(0, length);
    }

    return QString(length - numStr.size(), '0') + numStr;
}

LocalMessage LocalMessage::create(const QString &data) {
    if (data.size() < 36){
        return LocalMessage();
    }

    LocalMessage msg;
    msg.okey = true;
    msg.what = toInt(data, 0, 12);
    msg.arg1 = toInt(data, 12, 12);
    msg.arg2 = toInt(data, 24, 12);
    if (data.size() > 36){
        msg.str = data.mid(36);
    }

    return msg;
}

QString LocalMessage::toString(const LocalMessage &message) {
    return intToString(message.what, 12) + intToString(message.arg1, 12) + intToString(message.arg2, 12) + message.str;
}

std::atomic<bool> LocalMessage::sRegisterd = false;

void LocalMessage::registerThis() {
    if (!sRegisterd){
        sRegisterd = true;
        qRegisterMetaType<LocalMessage>("LocalMessage");
    }
}


}  // ~moon
