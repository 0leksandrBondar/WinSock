#pragma once

#include "socket.h"

#include <vector>

namespace bond
{
    namespace tcp
    {

        class Server
        {
        public:
            Server(AddressFamily family, short port);

            bool bind();
            bool listen();
            bool receive();
            bool receiveMessage(SOCKET clientSocket, std::vector<char>& buffer);

            SOCKET acceptClient();

        private:
            SocketAddress _listenAddr;
            bond::tcp::Socket _listenSocket;
        };

    } // namespace tcp

} // namespace bond
