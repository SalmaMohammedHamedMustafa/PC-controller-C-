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


    std::string clientMessage = httpHandeler.ParseRequest(clientRequest);

    // Handle different client messages (simple API commands)
    std::string responseBody;
    std::string response;
        if (clientMessage == "hi") {
            
            responseBody = "Hello, client!";
        } else if (clientMessage == "exit") {
            responseBody = "Goodbye!";
            response = httpHandeler.CreateResponse(responseBody);
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
            responseBody = "Unknown command.";
        }
        response = httpHandeler.CreateResponse(responseBody);
        server.SendData(const_cast<char*>(response.c_str()));
    
    
    return ConnectionState::RUNNING;
}



std::string Application::ManageFireLink(const std::string& website) {
    std::string responseBody;
    if (website == "facebook") {
        fireLink.firefox(fireLink.facebook);
        responseBody = "Opening Facebook...";
        return httpHandeler.CreateResponse(responseBody);
    } else if (website == "google") {
        fireLink.firefox(fireLink.google);
        responseBody = "Opening Google...";
        return httpHandeler.CreateResponse(responseBody);
    } else if (website == "youtube") {
        fireLink.firefox(fireLink.youtube);
        responseBody = "Opening YouTube...";
        return httpHandeler.CreateResponse(responseBody);
        }
    else if (website == "twitter") {
        fireLink.firefox(fireLink.twitter);
        responseBody = "Opening Twitter...";
        return httpHandeler.CreateResponse(responseBody);
    } else {
        responseBody = "Unknown website.";
        return httpHandeler.CreateResponse(responseBody);
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

    return httpHandeler.CreateResponse(responseBody);
}