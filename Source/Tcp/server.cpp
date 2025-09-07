#include "server.h"

#include <stdexcept>

namespace bond
{
    namespace network
    {
        SocketTCPServer::SocketTCPServer(AddressFamily addrFamily)
            : Socket(addrFamily, SocketType::TCP, Protocol::TCP)
        {
        }

        bool SocketTCPServer::bind(SocketAddress& address)
        {
            if (::bind(_socket, address.getSockAddr(), address.getSize()) == SOCKET_ERROR)
                return false;

            return true;
        }

        bool SocketTCPServer::listen(int backlog)
        {
            if (::listen(_socket, backlog) == SOCKET_ERROR)
                return false;

            return true;
        }

        SocketTCP SocketTCPServer::accept()
        {
            SOCKET clientSock = ::accept(_socket, nullptr, nullptr);
            if (clientSock == INVALID_SOCKET)
                throw std::runtime_error("accept failed");

            SocketTCP client(AddressFamily::IPv4);
            client.setSocket(clientSock);
            return client;
        }
    } // namespace network
} // namespace bond
