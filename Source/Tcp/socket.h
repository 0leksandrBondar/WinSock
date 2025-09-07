#include "Common/message.h"
#include "Common/socket.h"

namespace bond
{
    namespace network
    {
        class SocketTCP final : public Socket
        {
        public:
            SocketTCP(AddressFamily addrFamily);

            size_t recv(std::vector<char>& data) override;

            bool send(const Message& message);
            void send(const std::string& data);
            void send(const std::vector<char>& data) override;
        };
    } // namespace network
} // namespace bond
