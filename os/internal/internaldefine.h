#ifndef PLATFORM_OS_INTERNAL_INTERNALDEFINE_H
#define PLATFORM_OS_INTERNAL_INTERNALDEFINE_H

#include <functional>
#include <memory>

#include <QByteArray>

namespace moon {

class LocalSocket;
class LocalSocketConnector;
typedef std::shared_ptr<LocalSocket> LocalSocketPtr;

/**
 * @brief Defines a interface for the underlying connection to call when the connection has closed in an expected way.
 */
typedef std::function<void ()> OnDisconnectedListener;

/**
 * @brief Defines a interface for the underlying connection to call when it received some new data.
 */
typedef std::function<void (const QByteArray &data)> OnDataReceivedListener;

/**
 * @brief Defines a interface for the LocalServer to call when a new connection has established.
 */
typedef std::function<void (LocalSocketPtr &socket)> OnNewConnectionListener;

}  // ~moon

#endif // PLATFORM_OS_INTERNAL_INTERNALDEFINE_H
