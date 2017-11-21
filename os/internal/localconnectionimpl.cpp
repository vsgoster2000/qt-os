#include <os/internal/localconnectionimpl.h>

namespace moon {

LocalConnectionImpl::LocalConnectionImpl(LocalSocketPtr localSocket) : mLocalSocket(localSocket)
{

}

LocalConnectionImpl::~LocalConnectionImpl()
{

}

}  // ~moon
