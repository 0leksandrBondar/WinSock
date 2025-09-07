#include "socketaddress.h"

namespace bond
{
    namespace network
    {
        SocketAddress::SocketAddress(AddressFamily addrFamilyType, short port)
        {
            _sockAddrIn.sin_family = static_cast<short>(addrFamilyType);
            _sockAddrIn.sin_port = htons(port);
            _sockAddrIn.sin_addr.s_addr = htonl(INADDR_ANY);
        }

        SocketAddress::SocketAddress(AddressFamily addrFamily, short port,
                                     const std::string& ipAddress)
        {
            _sockAddrIn.sin_family = static_cast<short>(addrFamily);
            _sockAddrIn.sin_port = htons(port);
            inet_pton(AF_INET, ipAddress.c_str(), &_sockAddrIn.sin_addr);
        }
    } // namespace network
} // namespace bond
