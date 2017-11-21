#ifndef PLATFORM_OS_INTERNAL_LOCALSOCKETCONNECTOR_H
#define PLATFORM_OS_INTERNAL_LOCALSOCKETCONNECTOR_H

#include <os/internal/internaldefine.h>

#include <atomic>

#include <QString>

namespace moon{

class LocalSocketConnector
{
public:
    /**
     * @brief Connect to a QLocalServer specified by @serverName, this method will block the calling thread,
     * until connected to the server or an error occurs during connecting, this method at most block @timeoutMillis milliseconds.
     *
     * @param serverName a QString object represents the name of the server going to connect.
     * @param timeoutMillis a unsigned long number, the maximum time this method would block.
     *
     * @return Returns a valid LocalSocketPtr object on success, if on failure returns an empty LocalSocketPtr object.
     *
     */
    static LocalSocketPtr connectToServer(const QString &serverName, unsigned long timeoutMillis = 2000);
private:
    LocalSocketConnector(){}
    static std::atomic<unsigned long> sConnectionNo;
};



}  // ~moon
#endif // PLATFORM_OS_INTERNAL_LOCALSOCKETCONNECTOR_H
