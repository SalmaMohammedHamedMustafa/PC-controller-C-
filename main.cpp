#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>  // For close(), sleep()
#include <arpa/inet.h>  // For socket functions
#include "socket_handler/socket_handler.hpp"
#include "FireLink/FireLink.hpp"
#include "Application/Application.hpp"




int main() {
    // Create a TcpServerSocket object, bind it to a port, and start listening
    TcpServerSocket server(8080); // Listen on port 8080
    server.BindSocket();
    server.ListenForConnections(5); // Set the backlog to 5
    Application app;
    app.handleClient(server);

    return 0;
}
