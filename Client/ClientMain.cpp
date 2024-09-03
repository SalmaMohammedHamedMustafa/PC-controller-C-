#include <iostream>
#include "socket_handler/socket_handler.hpp"
#include "HTTPHandeler/HTTPHandeler.hpp"
constexpr char SERVER_IP[] = "192.168.1.5";
int main()
{
    TcpClientSocket client(const_cast<char*>(SERVER_IP));
    HTTPHandeler httpHandeler;
    client.ConnectToServer();
    std::string message = "hi";
    
    client.SendData(const_cast<char*>(httpHandeler.CreateResponse(message).c_str()));
    client.ReceiveData();
    std::cout << "Received message from server: " << client.GetBuffer() << std::endl;
    
    return 0;
}