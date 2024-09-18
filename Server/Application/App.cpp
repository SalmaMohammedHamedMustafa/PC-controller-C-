#include "App.hpp"
#include <iostream>
#include <string>



void Application::handleClient(TcpServerSocket& server) {
    state = ConnectionState::RUNNING;

    while (state == ConnectionState::RUNNING) {
        // Accept a client connection
        clientSocket = server.AcceptConnection();
        
        if (clientSocket < 0) {
            std::cout << "Error accepting client connection" << std::endl;
            state = ConnectionState::EXIT_REQUESTED;
            break;
        }

        while (server.isConnectionAlive(clientSocket)) {
            handleClientConnection(server);

            if (state == ConnectionState::EXIT_REQUESTED) {
                break;
            }
        }

        // Close the client socket once done
        close(clientSocket);
    }
}


/*
@brief: Handles the client connection and manages the client-server communication.
@param server: A reference to the TcpServerSocket object.
@return ConnectionState: The state of the connection.
*/

void Application::handleClientConnection(TcpServerSocket& server) {
    // Receive data from the client
    server.ReceiveData();
    std::string clientRequest = server.GetBuffer();
    std::cout << "Received from client:\n" << clientRequest << std::endl;
    std::string clientMessage = httpHandeler.ParseRequest(clientRequest);
    // Handle different client messages (simple API commands)
    std::string response;
    response = callCorrectAPI(clientMessage);
    server.SendData(const_cast<char*>(response.c_str()));
    

}


/*
@brief: iterates through the serverCommands map to find the correct function to call based on the client message.
@param clientMessage: The message received from the client.
@return std::string: The response message to send back to the client.
*/
std::string Application::callCorrectAPI(const std::string& clientMessage) {
    auto it = serverCommands.find(clientMessage);
    if (it != serverCommands.end()) {
        return (this->*(it->second))(clientMessage);
    } else {
        return manageUnknownCommand();
    }
}


/*
@brief: Manages the FireLink command to open a specific website in the browser.
@param website: The website to open.
@return std::string: The response message to send back to the client.
*/
std::string Application::manageFireLink(const std::string& website) {
    std::string responseBody;
    responseBody = "Opening " + website;
    std::cout << responseBody << std::endl;
    fireLink.firefox(website);
    return httpHandeler.CreateResponse(responseBody);
}


/*
@brief: Manages the device status command to get the battery percentage, CPU usage, RAM usage, or disk usage.
@param status: The device status to retrieve.
@return std::string: The response message to send back to the client.
*/
std::string Application::manageDeviceStatus(const std::string& statusType) {
    std::string responseBody;
    responseBody = deviceStatus.GetDeviceStatus(statusType);
    std::cout << responseBody << std::endl;
    return httpHandeler.CreateResponse(responseBody);
}

/*
@brief: Greets the client with a simple message.
@param clientMessage: The message received from the client.
@return std::string: The response message to send back to the client.
*/
std::string Application::greeteClient(const std::string& clientMessage) {
    
    return httpHandeler.CreateResponse("Hello, client!");
}

/*
@brief: Exits the client connection.
@param clientMessage: The message received from the client.
@return std::string: The response message to send back to the client.
*/
std::string Application::exitClient(const std::string& clientMessage) {
    state = ConnectionState::EXIT_REQUESTED;
    return httpHandeler.CreateResponse("Goodbye!");
}

/*
@brief: Manages an unknown command.
@return std::string: The response message to send back to the client.
*/
std::string Application::manageUnknownCommand() {
    return httpHandeler.CreateResponse("Unknown command.");
}