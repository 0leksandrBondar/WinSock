#pragma once

#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <string>

namespace bond
{
    enum class AddressFamily
    {
        IPv4 = AF_INET,
        IPv6 = AF_INET6,
    };

    enum class Protocol
    {
        TCP = IPPROTO_TCP,
        UDP = IPPROTO_UDP,
    };

    enum class SocketType
    {
        TCP = SOCK_STREAM,
        UDP = SOCK_DGRAM,
    };

    class SocketAddress
    {
    public:
        SocketAddress(AddressFamily addrFamily, short port);
        SocketAddress(AddressFamily addrFamily, short port, const std::string& ipAddress);

        socklen_t getSize() const { return sizeof(sockaddr_in); }
        sockaddr_in& getSockAddress() { return _sockAddrIn; }
        sockaddr* getSockAddr() { return reinterpret_cast<sockaddr*>(&_sockAddrIn); }

    private:
        sockaddr_in _sockAddrIn{};
    };

} // namespace bond
