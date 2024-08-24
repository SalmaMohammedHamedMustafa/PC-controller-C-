#include <iostream>
#include "socket_handler/socket_handler.hpp"

int main() {
    // Create a TcpClientSocket object and connect to the server
    char serverIp[] = "192.168.1.6"; // Replace with the actual server IP address
    TcpClientSocket client(serverIp);
    client.ConnectToServer();

    // Send a message to the server
    char message[] = "Hello, server!";
    client.SendData(message);

    // Receive a response from the server
    client.ReceiveData();
    std::cout << "Received from server: " << client.GetBuffer() << std::endl;

    return 0;
}