#include "wsadata.h"

namespace bond
{
    bool WsaData::startup() { return WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0; }

    bool WsaData::cleanup() { return WSACleanup(); }

} // namespace bond
