#include "wsadata.h"

namespace bond
{
    namespace network
    {
        bool WsaData::startup() { return WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0; }

        bool WsaData::cleanup() { return WSACleanup(); }
    } // namespace network
} // namespace bond
