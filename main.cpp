
#include <iostream>
#include "socket_handler/socket_handler.hpp"

char Ip[]= "192.168.1.6";
char message[] = "hi";
int main()
{
    TcpSocket MySocket(Ip);
    MySocket.ConnectToServer();
    MySocket.SendData(message);
    MySocket.ReceiveData();
    std::cout<<MySocket.GetBuffer()<<"\n";
    return 0;
}