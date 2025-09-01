#pragma once

#include "socketaddress.h"

namespace bond
{

    namespace tcp
    {
        class Socket
        {
        public:
            Socket(bond::AddressFamily addrFamily = AddressFamily::IPv4);
            ~Socket() { closesocket(_socket); }

            bool conncetBySockAddr(SocketAddress& sockAddress);

            bool send(const char* data);

            [[nodiscard]] SOCKET& getSocket() { return _socket; }

        private:
            SOCKET _socket{ INVALID_SOCKET };
            bond::AddressFamily _addressFamily;
        };

    } // namespace tcp
} // namespace bond
