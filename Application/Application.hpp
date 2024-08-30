#include "../socket_handler/socket_handler.hpp"
#include "../FireLink/FireLink.hpp"
#include "../GetDeviceStatus/GetDeviceStatus.hpp"
#include <string>

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
        /*
        @brief: Handles the client connection and manages the client-server communication.
        @param server: A reference to the TcpServerSocket object.
        @return ConnectionState: The state of the connection.
        */
        ConnectionState HandleClientConnection(TcpServerSocket& server);
        /*
        @brief: Parses the client request to extract the message body.
        @param request: The client request string.
        @return std::string: The message body extracted from the request.
        */
        std::string ParseRequest(const std::string& request);
        /*
        @brief: Manages the FireLink command to open a specific website in the browser.
        @param website: The website to open.
        @return std::string: The response message to send back to the client.
        */
        std::string ManageFireLink(const std::string& website);

        /*
        @brief: Manages the device status command to get the battery percentage, CPU usage, RAM usage, or disk usage.
        @param status: The device status to retrieve.
        @return std::string: The response message to send back to the client.
        */
        std::string ManageDeviceStatus(const std::string& status);

};
