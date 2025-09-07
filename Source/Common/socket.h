#pragma once

#include "socketaddress.h"

#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <vector>

namespace bond
{
    namespace network
    {

        class Socket
        {
        public:
            Socket(const Socket&) = delete;
            Socket& operator=(const Socket&) = delete;

            Socket(AddressFamily addrFamily, SocketType socketType, Protocol protocol);
            Socket& operator=(Socket&& other) noexcept;
            Socket(Socket&& other) noexcept;

            ~Socket();

            bool connectTo(SocketAddress& address);
            void setSocket(SOCKET socket) { _socket = socket; }

            virtual size_t recv(std::vector<char>& data) = 0;
            virtual void send(const std::vector<char>& data) = 0;

            [[nodiscard]] SOCKET& getSocket() { return _socket; }

        protected:
            SOCKET _socket;
        };
    } // namespace network
} // namespace bond
