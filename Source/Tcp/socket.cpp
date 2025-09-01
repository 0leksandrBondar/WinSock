#include "socket.h"

namespace bond
{
    namespace tcp
    {

        Socket::Socket(AddressFamily addrFamily) : _addressFamily{ addrFamily }
        {
            _socket = socket(static_cast<int>(_addressFamily), static_cast<int>(SocketType::TCP),
                             static_cast<int>(Protocol::TCP));
        }

        bool Socket::conncetBySockAddr(SocketAddress& sockAddress)
        {
            if (::connect(_socket, sockAddress.getSockAddr(), sockAddress.getSize())
                == SOCKET_ERROR)
                return false;

            return true;
        }

        bool Socket::send(const char* data)
        {
            if (::send(_socket, data, strlen(data), 0) == SOCKET_ERROR)
                return -1;

            return true;
        }

    } // namespace tcp

} // namespace bond
