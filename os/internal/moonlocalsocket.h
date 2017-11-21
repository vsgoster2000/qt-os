#ifndef MOONLOCALSOCKET_H
#define MOONLOCALSOCKET_H

#include <QLocalSocket>
#include <QDebug>

namespace moon {

class MoonLocalSocket : public QLocalSocket{
public:
    MoonLocalSocket(const QString connectionName) : mConnectionName(connectionName){
        qDebug() << "MoonLocalSocket#constructor-->" << mConnectionName;
    }

    ~MoonLocalSocket(){
        qDebug() << "MoonLocalSocket#deconstructor-->" << mConnectionName;
    }

private:
    const QString mConnectionName;
};


}

#endif // MOONLOCALSOCKET_H
