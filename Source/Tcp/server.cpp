#include "server.h"

namespace bond
{
    namespace tcp
    {

        Server::Server(AddressFamily family, short port)
            : _listenSocket(), _listenAddr(family, port)
        {
        }

        bool Server::bind()
        {
            return ::bind(_listenSocket.getSocket(), _listenAddr.getSockAddr(),
                          _listenAddr.getSize())
                   != SOCKET_ERROR;
        }

        bool Server::listen()
        {
            return ::listen(_listenSocket.getSocket(), SOMAXCONN) != SOCKET_ERROR;
        }

        SOCKET Server::acceptClient()
        {
            sockaddr_in clientAddr;
            int clientSize = sizeof(clientAddr);

            SOCKET clientSocket
                = ::accept(_listenSocket.getSocket(), (sockaddr*)&clientAddr, &clientSize);

            if (clientSocket == INVALID_SOCKET)
                return INVALID_SOCKET;

            return clientSocket;
        }

        bool Server::receiveMessage(SOCKET clientSocket, std::vector<char>& buffer)
        {
            int bytesReceived = ::recv(clientSocket, buffer.data(), sizeof(buffer) - 1, 0);

            if (bytesReceived > 0)
            {
                buffer[bytesReceived] = '\0';
                buffer.clear();
                return true;
            }
            return false;
        }
    } // namespace tcp

} // namespace bond
