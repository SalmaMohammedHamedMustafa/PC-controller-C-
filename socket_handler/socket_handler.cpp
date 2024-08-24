#include <iostream>
#include "socket_handler.hpp"

/**
 * @brief Constructs a TcpSocket object and initializes the socket.
 * @param WantedServerIp A pointer to a character array representing the server's IP address.
 * 
 * This constructor creates a socket and sets up the server address structure.
 */
TcpSocket::TcpSocket(char* WantedServerIp) {
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
    serverAddr.sin_addr.s_addr = inet_addr(ServerIp); // Server IP address
}

/**
 * @brief Connects the client socket to the server.
 * 
 * Attempts to establish a connection to the server using the provided server address.
 * If the connection fails, an exception is thrown, and the socket is closed.
 * 
 * @throw std::runtime_error If the connection fails.
 */
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

/**
 * @brief Sends data to the connected server.
 * 
 * @param message A pointer to a character array containing the message to be sent.
 */
void TcpSocket::SendData(char* message) {
    send(clientSocket, message, strlen(message), 0);
}

/**
 * @brief Receives data from the connected server.
 * 
 * This function reads data from the server and prints it to the console.
 */
void TcpSocket::ReceiveData() {
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        std::cout << "Received from server: " << buffer << std::endl;
    }
}

/**
 * @brief Retrieves the buffer containing received data.
 * 
 * @return char* A pointer to the buffer containing data received from the server.
 */
char* TcpSocket::GetBuffer() {
    return buffer;
}

/**
 * @brief Destructor for the TcpSocket class.
 * 
 * Closes the client socket when the TcpSocket object is destroyed.
 */
TcpSocket::~TcpSocket() {
    close(clientSocket);
}