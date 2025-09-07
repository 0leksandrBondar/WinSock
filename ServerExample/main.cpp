#include "Common/message.h"
#include "Common/wsadata.h"
#include "server.h"

#include "spdlog/spdlog.h"

bond::network::Message recvMessage(bond::network::SocketTCP& client)
{
    // 1. read header
    bond::network::Header header{};
    size_t received = 0;
    char* headerPtr = reinterpret_cast<char*>(&header);

    while (received < sizeof(header))
    {
        int ret = ::recv(client.getSocket(), headerPtr + received,
                         static_cast<int>(sizeof(header) - received), 0);
        if (ret <= 0)
            throw std::runtime_error("Failed to receive header");
        received += ret;
    }

    std::string type(header.messageType, strnlen(header.messageType, sizeof(header.messageType)));
    spdlog::info("Header received: type={} totalSize={} totalPackets={}", type, header.totalSize,
                 header.totalPackets);

    // 2. read body
    std::vector<char> body(header.totalSize);
    size_t totalReceived = 0;

    while (totalReceived < header.totalSize)
    {
        int ret = ::recv(client.getSocket(), body.data() + totalReceived,
                         static_cast<int>(header.totalSize - totalReceived), 0);
        if (ret <= 0)
            throw std::runtime_error("Failed to receive body");
        totalReceived += ret;
    }

    return bond::network::Message(type, body, header.packetSize);
}

int main()
{
    bond::network::WsaData wsaData;
    wsaData.startup();

    bond::network::SocketTCPServer server(bond::network::AddressFamily::IPv4);
    bond::network::SocketAddress addr(bond::network::AddressFamily::IPv4, 12345, "0.0.0.0");

    if (!server.bind(addr))
    {
        spdlog::error("Bind failed");
        return -1;
    }

    if (!server.listen())
    {
        spdlog::error("Listen failed");
        return -1;
    }

    spdlog::info("Server is listening on port 12345...");

    while (true)
    {
        try
        {
            auto client = server.accept();
            spdlog::info("New client connected!");

            auto message = recvMessage(client);

            std::string text(message.body().begin(), message.body().end());
            spdlog::info("Received body: {}", text);

            // 3. Отправка ответа
            const std::string reply = "Hello from server!";
            client.send(std::vector<char>(reply.begin(), reply.end()));
        }
        catch (const std::exception& e)
        {
            spdlog::error("Error: {}", e.what());
        }
    }

    return 0;
}
