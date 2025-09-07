#pragma once

#include "Common/socket.h"
#include "socket.h"

namespace bond
{
    namespace network
    {
        class SocketTCPServer final : public Socket
        {
        public:
            SocketTCPServer(AddressFamily addrFamily);

            bool bind(SocketAddress &address);
            bool listen(int backlog = SOMAXCONN);
            SocketTCP accept();

            void send(const std::vector<char>& data) override { /* сервер напрямую не шлёт */ }

            size_t recv(std::vector<char>& data) override
            {
                return 0; /* сервер напрямую не читает */
            }
        };
    } // namespace network
} // namespace bond
