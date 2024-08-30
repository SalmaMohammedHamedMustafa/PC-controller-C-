#include "Application.hpp"
#include <iostream>
#include <string>


void Application::handleClient(TcpServerSocket& server) {
    ConnectionState state = ConnectionState::RUNNING;

    while (state == ConnectionState::RUNNING) {
        // Accept a client connection
        clientSocket = server.AcceptConnection();
        
        if (clientSocket < 0) {
            std::cout << "Error accepting client connection" << std::endl;
            break;
        }

        while (server.isConnectionAlive(clientSocket)) {
            state = HandleClientConnection(server);

            if (state == ConnectionState::EXIT_REQUESTED) {
                break;
            }
        }

        // Close the client socket once done
        close(clientSocket);
    }
}

ConnectionState Application::HandleClientConnection(TcpServerSocket& server) {
    // Receive data from the client
    server.ReceiveData();
    std::string clientRequest = server.GetBuffer();
    std::cout << "Received from client:\n" << clientRequest << std::endl;


    std::string clientMessage = ParseRequest(clientRequest);

    // Handle different client messages (simple API commands)
    std::string response;
        if (clientMessage == "hi") {
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, client!";
        } else if (clientMessage == "exit") {
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 8\r\n\r\nGoodbye!";
            server.SendData(const_cast<char*>(response.c_str()));
            return ConnectionState::EXIT_REQUESTED;
        }
        else if (clientMessage.find("website")==0)
        {
            std::string url = clientMessage.substr(8);
            response = ManageFireLink(url);
        }
        else if (clientMessage.find("deviceStatus")==0) {
            std::string status = clientMessage.substr(12);
            response = ManageDeviceStatus(status);
            std::cout << response << std::endl;
        }
        else {
            response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 15\r\n\r\nUnknown command.";
        }

        server.SendData(const_cast<char*>(response.c_str()));
    
    
    return ConnectionState::RUNNING;
}

std::string Application::ParseRequest(const std::string& request) {
    // Find the position of the end of the headers
    size_t pos = request.find("\r\n\r\n");
    if (pos != std::string::npos) {
        // Extract the message body from the request
        std::string clientMessage = request.substr(pos + 4);
        return clientMessage;
    }
    return "";
}

std::string Application::ManageFireLink(const std::string& website) {
    if (website == "facebook") {
        fireLink.firefox(fireLink.facebook);
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nOpen Facebook...";
    } else if (website == "google") {
        fireLink.firefox(fireLink.google);
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nOpen Google...";
    } else if (website == "youtube") {
        fireLink.firefox(fireLink.youtube);
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nOpen YouTube...";
    } else if (website == "twitter") {
        fireLink.firefox(fireLink.twitter);
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nOpen Twitter...";
    } else {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nUnknown website.";
    }
}

// Application method to manage device status
std::string Application::ManageDeviceStatus(const std::string& status) {
    std::string responseBody;

    if (status == "battery") {
        responseBody = deviceStatus.GetBatteryPercentage();
    } else if (status == "cpu") {
        responseBody = deviceStatus.GetCPUUsage();
    } else if (status == "ram") {
        responseBody = deviceStatus.GetRAMUsage();
    } else if (status == "disk") {
        responseBody = deviceStatus.GetDiskUsage();
    } else {
        responseBody = "Unknown status.";
    }

    return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: " + std::to_string(responseBody.length()) + "\r\n\r\n" + responseBody;
}