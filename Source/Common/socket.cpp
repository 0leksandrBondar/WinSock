#include "socket.h"

namespace bond
{
    namespace network
    {

        Socket::Socket(AddressFamily addrFamily, SocketType socketType, Protocol protocol)
        {
            _socket = socket(static_cast<int>(addrFamily), static_cast<int>(socketType),
                             static_cast<int>(protocol));
        }

        Socket& Socket::operator=(Socket&& other) noexcept
        {
            if (this != &other)
            {
                if (_socket != INVALID_SOCKET)
                    closesocket(_socket);

                _socket = other._socket;
                other._socket = INVALID_SOCKET;
            }
            return *this;
        }

        Socket::Socket(Socket&& other) noexcept : _socket(other._socket)
        {
            other._socket = INVALID_SOCKET;
        }

        Socket::~Socket()
        {
            if (_socket != INVALID_SOCKET)
                closesocket(_socket);
        }

        bool Socket::connectTo(SocketAddress& address)
        {
            if (::connect(_socket, address.getSockAddr(), address.getSize()) == SOCKET_ERROR)
                return false;

            return true;
        }

    } // namespace network
} // namespace bond
