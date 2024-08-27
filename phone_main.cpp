#include <cstring>      // For memset()
#include <string>
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For inet_addr() and sockaddr_in
#include <unistd.h>     // For close()
#include <iostream>

/**
 * @brief Abstract base class for handling TCP socket connections.
 */
class TcpSocket {
protected:
    char buffer[1024] = {0};   ///< Buffer for receiving data

public:
    /**
     * @brief Sends data through the socket.
     * @param message A pointer to a character array containing the message to be sent.
     */
    virtual void SendData(char* message) = 0;

    /**
     * @brief Receives data from the socket.
     * This function reads data from the socket and stores it in the buffer.
     */
    virtual void ReceiveData() = 0;

    /**
     * @brief Retrieves the buffer containing received data.
     * @return char* A pointer to the buffer containing data received from the socket.
     */
    virtual char* GetBuffer() = 0;

    /**
     * @brief Virtual destructor for the TcpSocket class.
     */
    virtual ~TcpSocket() = default;
};

/**
 * @brief TcpClientSocket class for handling TCP client-side connections.
 */
class TcpClientSocket : public TcpSocket {
    int clientSocket;          ///< File descriptor for the client socket
    sockaddr_in serverAddr;    ///< Structure for server address
    char* ServerIp;            ///< Pointer to the server IP address

public:
    TcpClientSocket(char* WantedServerIp);

    bool isConnectionAlive();


    void ConnectToServer();
    void SendData(char* message) override;
    void ReceiveData() override;
    char* GetBuffer() override;
    ~TcpClientSocket();
};

/**
 * @brief TcpServerSocket class for handling TCP server-side connections.
 */
class TcpServerSocket : public TcpSocket {
    int serverSocket;              ///< File descriptor for the server socket
    int clientSocket;              ///< File descriptor for the client socket
    sockaddr_in serverAddr;        ///< Structure for server address
    sockaddr_in clientAddr;        ///< Structure for client address

public:
    TcpServerSocket(int port);
    void BindSocket();
    void ListenForConnections(int backlog);
    int AcceptConnection();
    void SendData(char* message) override;
    void ReceiveData() override;
    char* GetBuffer() override;
    ~TcpServerSocket();
};

// TcpClientSocket method implementations

TcpClientSocket::TcpClientSocket(char* WantedServerIp) {
    try {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket < 0) {
            throw std::runtime_error("Error creating socket!");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    ServerIp = WantedServerIp;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr(ServerIp);
}

void TcpClientSocket::ConnectToServer() {
    try {
        int connectionStatus = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
        if (connectionStatus < 0) {
            throw std::runtime_error("Error connecting to server!");
        }

        std::cout << "Connected to server successfully!" << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        close(clientSocket);
    }
}

bool TcpClientSocket::isConnectionAlive() {
    char buffer;
    ssize_t result = recv(clientSocket, &buffer, 1, MSG_PEEK);

    if (result > 0) {
        // Data is available to read, connection is alive
        return true;
    } else if (result == 0) {
        // Connection has been closed by the peer
        return false;
    } else {
        // Error occurred
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            // No data to read right now, but the connection is still alive
            return true;
        } else {
            // Some other error occurred, consider the connection as closed
            return false;
        }
    }
}

void TcpClientSocket::SendData(char* message) {
    send(clientSocket, message, strlen(message), 0);
}

void TcpClientSocket::ReceiveData() {
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0'; // Null-terminate the received data
}

char* TcpClientSocket::GetBuffer() {
    return buffer;
}

TcpClientSocket::~TcpClientSocket() {
    close(clientSocket);
}

// TcpServerSocket method implementations

TcpServerSocket::TcpServerSocket(int port) {
    try {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            throw std::runtime_error("Error creating server socket!");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
}

void TcpServerSocket::BindSocket() {
    try {
        int bindStatus = bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
        if (bindStatus < 0) {
            throw std::runtime_error("Error binding server socket!");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        close(serverSocket);
    }
}

void TcpServerSocket::ListenForConnections(int backlog) {
    try {
        int listenStatus = listen(serverSocket, backlog);
        if (listenStatus < 0) {
            throw std::runtime_error("Error listening on server socket!");
        }
        std::cout << "Server is listening for connections..." << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        close(serverSocket);
    }
}

int TcpServerSocket::AcceptConnection() {
    socklen_t addrLen = sizeof(clientAddr);
    try {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &addrLen);
        if (clientSocket < 0) {
            throw std::runtime_error("Error accepting client connection!");
        }
        std::cout << "Client connected successfully!" << std::endl;
        return clientSocket;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        close(serverSocket);
        return -1;
    }
}

void TcpServerSocket::SendData(char* message) {
    send(clientSocket, message, strlen(message), 0);
}

void TcpServerSocket::ReceiveData() {
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0'; // Null-terminate the received data
}

char* TcpServerSocket::GetBuffer() {
    return buffer;
}

TcpServerSocket::~TcpServerSocket() {
    close(clientSocket);
    close(serverSocket);
}

// Main function



#include <iostream>

int main() {
    // Create a TcpClientSocket object and connect to the server
    char serverIp[] = "192.168.1.5"; // Replace with the actual server IP address
    TcpClientSocket client(serverIp);
    client.ConnectToServer();
    // Main loop for continuously sending user input to the server
    while (true) {
        // Get user input
        std::string userInput;
        std::cout << "Enter a message to send to the server: ";
        std::getline(std::cin, userInput);
        std::cin.clear();
        // Check if the user wants to exit
        if (userInput == "exit") {
            break; // Exit the loop and close the program
        }

        // Send the user input to the server
        char* message = new char[userInput.size() + 1]; // Allocate a new buffer
        std::strcpy(message, userInput.c_str());
        client.SendData(message);
        delete[] message; // Don't forget to free the memory
        std::cout<<"sent\n";
        // Receive a response from the server
        client.ReceiveData();
        std::cout << "Received from server: " << client.GetBuffer() << std::endl;
        std::cout<<"reccieved\n";
    }

    return 0;
}