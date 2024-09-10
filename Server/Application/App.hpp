#ifndef APP_HPP
#define APP_HPP


#include "../socket_handler/socket_handler.hpp"
#include "../FireLink/FireLink.hpp"
#include "../GetDeviceStatus/GetDeviceStatus.hpp"
#include "../HTTPHandeler/HTTPHandeler.hpp"
#include <string>
#include <map>

enum class ConnectionState {
    RUNNING,
    EXIT_REQUESTED
};

class Application {
public:
    /*
    @brief: Handles the client connection and manages the client-server communication.
    @param server: A reference to the TcpServerSocket object.
    */
    void handleClient(TcpServerSocket& server);

private:
    int clientSocket;
    FireLink fireLink;
    DeviceStatus deviceStatus;
    HTTPHandeler httpHandeler;
    ConnectionState state;

    std::string callCorrectAPI(const std::string& clientMessage);

    void handleClientConnection(TcpServerSocket& server);

    std::string manageFireLink(const std::string& website);

    std::string manageDeviceStatus(const std::string& statusType);

    std::string greeteClient(const std::string& clientMessage);

    std::string exitClient(const std::string& clientMessage);

    std::string manageUnknownCommand();

   //map of server commands to functions
    std::map<std::string, std::string (Application::*)(const std::string&)> serverCommands = {
        {"hi", &Application::greeteClient},
        {"exit", &Application::exitClient},
        {"website", &Application::manageFireLink},
        {"deviceStatus", &Application::manageDeviceStatus}
    };

};

#endif // APP_HPP