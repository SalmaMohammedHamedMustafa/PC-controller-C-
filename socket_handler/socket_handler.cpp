#include <iostream>
#include "socket_handler.hpp"

TcpSocket::TcpSocket(char* WantedServerIp)
{
    try {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket < 0) {
            throw std::runtime_error("Error creating socket!");
        }

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        
    }
    ServerIp = WantedServerIp;
    serverAddr.sin_family = AF_INET;          // IPv4
    serverAddr.sin_port = htons(8080);        // Port number to connect to
    serverAddr.sin_addr.s_addr = inet_addr(ServerIp); // Server IP address (replace with your server's IP)
}


void TcpSocket::ConnectToServer() {
    try {
        int connectionStatus = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
        if (connectionStatus < 0) {
            throw std::runtime_error("Error connecting to server!");
        }

        std::cout << "Connected to server successfully!" << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        close(clientSocket); // Close the socket on error
    }
}


void TcpSocket::SendData(char* message)
{
    send(clientSocket, message, strlen(message), 0);
}

void TcpSocket::ReceiveData()
{
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        std::cout << "Received from server: " << buffer << std::endl;
    }
}

char* TcpSocket::GetBuffer()
{
    return buffer;
}

TcpSocket::~TcpSocket()
{
    close(clientSocket);
}