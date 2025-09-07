#include "Common/message.h"
#include "Common/wsadata.h"
#include "socket.h"

#include "spdlog/spdlog.h"

int main()
{
    bond::network::WsaData wsaData;
    wsaData.startup();

    bond::network::SocketTCP socket(bond::network::AddressFamily::IPv4);

    bond::network::SocketAddress serverAddr(bond::network::AddressFamily::IPv4, 12345, "127.0.0.1");

    if (socket.connectTo(serverAddr))
        spdlog::info("Connection to serverAddr successful");

    const std::string messageType = "textMessage";
    const std::string body = "Hello from client";

    std::vector<char> msg(body.size());
    std::memcpy(msg.data(), body.data(), body.size() * sizeof(char));

    bond::network::Message message(messageType, msg);

    socket.send(message);

    while (true)
    {
    }

    return 0;
}
