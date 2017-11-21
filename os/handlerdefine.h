#ifndef PLATFORM_OS_HANDLERDEFINE_H
#define PLATFORM_OS_HANDLERDEFINE_H

#include <functional>
#include <memory>

namespace moon {

class Message;
class Handler;

/**
 * @brief A Handler object use a MessageHandler object to handle its message.
 *
 * A MessageHandler object can be considered as a function with such signature(void (const Message&)),
 * Which takes a constant reference to a Message object as its single argument and returns void.
 *
 * Generally, use boost::bind to generate a MessageHandler object.
 *
 * Example: MessageHandler handler = boost::bind(the function you want to convert to MessageHandler);
 */
typedef std::function<void (const Message&)> MessageHandler;

/**
 * @brief A Runnable object can be considered as a callable unit.
 * A handler object can post an Runnable object to its associated thread in which this callable unit will be called.
 * And client can use ThreadRunnable to wrapper a runnable as a callable unit, and then use the QThreadPoll to call this unit.
 *
 * A Runnable object can also be considered as a pointer to a function with such signature(void ()),
 * which takes no arguments and returns void.
 *
 * Generally, use boost::bind to generate a Runnable object.
 *
 * Example: Runnable handler = boost::bind(the function you want to convert to Runnable);
 */
typedef std::function<void ()> Runnable;
typedef std::shared_ptr<Handler> HandlerPtr;

}


#endif // PLATFORM_OS_HANDLERDEFINE_H
