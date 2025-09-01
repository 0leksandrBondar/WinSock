#include "server.h"
#include "wsadata.h"

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex clientsMutex;

void acceptClientsTaks(std::vector<SOCKET>& conteiner, bond::tcp::Server& server)
{
    std::thread(
        [&]()
        {
            while (true)
            {
                SOCKET newSock = server.acceptClient();
                if (newSock != INVALID_SOCKET)
                {
                    std::lock_guard<std::mutex> lock(clientsMutex);
                    conteiner.push_back(newSock);
                }
            }
        })
        .detach();
}

void receiveMessage(std::vector<SOCKET>& connectedClients, bond::tcp::Server& server)
{
    std::thread(
        [&]()
        {
            std::vector<char> data(4096);
            while (true)
            {
                {
                    std::lock_guard<std::mutex> lock(clientsMutex);

                    for (auto it = connectedClients.begin(); it != connectedClients.end();)
                    {
                        if (!server.receiveMessage(*it, data))
                        {
                            std::cout << "Client disconnected\n";
                            closesocket(*it);
                            it = connectedClients.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        })
        .detach();
}

int main()
{
    bond::WsaData data;
    data.startup();

    std::vector<SOCKET> _clients;

    bond::tcp::Server serverSocket(bond::AddressFamily::IPv4, 12345);
    serverSocket.bind();
    serverSocket.listen();

    acceptClientsTaks(_clients, serverSocket);
    receiveMessage(_clients, serverSocket);

    while (true)
    {
    }

    return 0;
}
