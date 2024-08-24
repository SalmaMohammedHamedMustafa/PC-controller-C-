#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <cstring>      // For memset()
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For inet_addr() and sockaddr_in
#include <unistd.h>     // For close()

class TcpSocket {
    int clientSocket;
    sockaddr_in serverAddr;
    char* ServerIp;
    char buffer[1024] = {0};

public:
    TcpSocket(char* WantedServerIp);
    void ConnectToServer();
    void SendData(char* message);
    void ReceiveData();
    char* GetBuffer();
    ~TcpSocket();
};

#endif // TCPSOCKET_H