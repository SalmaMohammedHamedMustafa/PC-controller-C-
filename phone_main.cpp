#include <cstring>      // For memset()
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

char Ip[] = "192.168.1.6";
char message[] = "hi";
int main()
{
    // Create a TcpServerSocket object, bind it to a port, and start listening
    TcpServerSocket server(8080); // Listen on port 8080
    server.BindSocket();
    server.ListenForConnections(5); // Set the backlog to 5

    // Accept a client connection
    int clientSocket = server.AcceptConnection();

    // Receive data from the client
    server.ReceiveData();
    std::cout << "Received from client: " << server.GetBuffer() << std::endl;

    // Send a response back to the client
    char response[] = "Hello, client!";
    server.SendData(response);

    return 0;
}
