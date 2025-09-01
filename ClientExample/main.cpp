#include "socket.h"
#include "wsadata.h"

int main()
{
    bond::WsaData data;
    data.startup();

    bond::tcp::Socket socket;
    bond::SocketAddress serverAddr(bond::AddressFamily::IPv4, 12345, "127.0.0.1");

    socket.conncetBySockAddr(serverAddr);
    socket.send("Hello from client");

    while (true)
    {
    }

    return 0;
}
