#include "../socket_handler/socket_handler.hpp"
#include "../FireLink/FireLink.hpp"
#include <string>

enum class ConnectionState {
    RUNNING,
    EXIT_REQUESTED
};

class Application {
    public:
        void handleClient(TcpServerSocket& server);
    private:
        int clientSocket;
        FireLink fireLink;
        ConnectionState HandleClientConnection(TcpServerSocket& server);
        std::string ParseRequest(const std::string& request);
        std::string ManageFireLink(const std::string& website);

};
