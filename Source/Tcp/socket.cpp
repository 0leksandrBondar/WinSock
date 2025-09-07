#include "socket.h"

#include <stdexcept>

namespace bond
{
    namespace network
    {

        SocketTCP::SocketTCP(AddressFamily addrFamily)
            : Socket(addrFamily, SocketType::TCP, Protocol::TCP)
        {
        }

        size_t SocketTCP::recv(std::vector<char>& data)
        {
            size_t received = ::recv(_socket, data.data(), static_cast<int>(data.size()), 0);

            if (received == 0)
                return 0;
            else if (received == SOCKET_ERROR)
            {
                int err = WSAGetLastError();
                throw std::runtime_error("recv failed with error: " + std::to_string(err));
            }

            return received;
        }

        bool SocketTCP::send(const Message& message)
        {
            const char* headerPtr = reinterpret_cast<const char*>(&message.header());
            int headerSize = sizeof(Header);

            int sent = ::send(_socket, headerPtr, headerSize, 0);
            if (sent == SOCKET_ERROR || sent != headerSize)
            {
                int err = WSAGetLastError();
                throw std::runtime_error("send header failed: " + std::to_string(err));
            }

            const auto& body = message.body();
            for (uint32_t i = 0; i < message.header().totalPackets; ++i)
            {
                size_t offset = i * message.header().packetSize;
                size_t size = std::min<size_t>(message.header().packetSize, body.size() - offset);

                int bodySent = ::send(_socket, body.data() + offset, static_cast<int>(size), 0);
                if (bodySent == SOCKET_ERROR || bodySent != size)
                {
                    int err = WSAGetLastError();
                    throw std::runtime_error("send body failed: " + std::to_string(err));
                }
            }

            return true;
        }

        void SocketTCP::send(const std::string& data)
        {
            std::vector<char> buffer(data.begin(), data.end());
            send(buffer);
        }

        void SocketTCP::send(const std::vector<char>& data)
        {
            size_t totalSent = 0;
            const size_t dataSize = data.size();
            while (totalSent < dataSize)
            {
                const int sent = ::send(_socket, data.data() + totalSent,
                                        static_cast<int>(dataSize - totalSent), 0);

                if (sent == SOCKET_ERROR)
                {
                    int err = WSAGetLastError();
                    throw std::runtime_error("send failed with error: " + std::to_string(err));
                }

                totalSent += sent;
            }
        }

    } // namespace network

} // namespace bond
