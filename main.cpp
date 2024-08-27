#include <iostream>
#include "socket_handler/socket_handler.hpp"
#include "FireLink/FireLink.hpp"

int main() {
    // Create a TcpServerSocket object, bind it to a port, and start listening
    TcpServerSocket server(8080); // Listen on port 8080
    server.BindSocket();
    server.ListenForConnections(5); // Set the backlog to 5
    FireLink fireLink; // Create an instance of the FireLink class
        // Accept a client connection
        int clientSocket = server.AcceptConnection();

        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection." << std::endl;
        }

    while (true) {

        if (!server.isConnectionAlive(clientSocket))
        {
            break;
        }

        server.ReceiveData();
        std::string clientMessage = server.GetBuffer();
        std::cout << "Received from client: " << clientMessage << std::endl;

        // Handle different client messages
        if (clientMessage == "hi") {
            char response[] = "Hello, client!";
            server.SendData(response);
        } else if (clientMessage == "1") {
            fireLink.firefox(fireLink.facebook_link);
            char response[] = "Facebook opened";
            server.SendData(response);
        } else if (clientMessage == "2") {
            fireLink.firefox(fireLink.google_link);
            char response[] = "Google opened";
            server.SendData(response);
        } else if (clientMessage == "3") {
            fireLink.firefox(fireLink.youtube_link);
            char response[] = "YouTube opened";
            server.SendData(response);
        } else if (clientMessage == "4") {
            fireLink.firefox(fireLink.twitter_link);
            char response[] = "Twitter opened";
            server.SendData(response);
        }
    }

    return 0;
}
