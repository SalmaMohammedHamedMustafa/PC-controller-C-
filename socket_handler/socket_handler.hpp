#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <cstring>      // For memset()
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For inet_addr() and sockaddr_in
#include <unistd.h>     // For close()

/**
 * @brief TcpSocket class for handling TCP socket connections.
 */
class TcpSocket {
    int clientSocket;          ///< File descriptor for the client socket
    sockaddr_in serverAddr;    ///< Structure for server address
    char* ServerIp;            ///< Pointer to the server IP address
    char buffer[1024] = {0};   ///< Buffer for receiving data

public:
    /**
     * @brief Constructs a TcpSocket object and initializes the socket.
     * @param WantedServerIp A pointer to a character array representing the server's IP address.
     */
    TcpSocket(char* WantedServerIp);

    /**
     * @brief Connects the client socket to the server.
     * @throw std::runtime_error If the connection fails.
     */
    void ConnectToServer();

    /**
     * @brief Sends data to the connected server.
     * @param message A pointer to a character array containing the message to be sent.
     */
    void SendData(char* message);

    /**
     * @brief Receives data from the connected server.
     * This function reads data from the server and prints it to the console.
     */
    void ReceiveData();

    /**
     * @brief Retrieves the buffer containing received data.
     * @return char* A pointer to the buffer containing data received from the server.
     */
    char* GetBuffer();

    /**
     * @brief Destructor for the TcpSocket class.
     * Closes the client socket when the TcpSocket object is destroyed.
     */
    ~TcpSocket();
};

#endif // TCPSOCKET_H