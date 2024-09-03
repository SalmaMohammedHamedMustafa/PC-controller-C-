#include "HTTPHandeler.hpp"

std::string HTTPHandeler::ParseRequest(const std::string& request) {
    // Find the position of the end of the headers
    size_t pos = request.find("\r\n\r\n");
    if (pos != std::string::npos) {
        // Extract the message body from the request
        std::string clientMessage = request.substr(pos + 4);
        return clientMessage;
    }
    return "";
}

std::string HTTPHandeler::CreateResponse(const std::string& ResponseContent) {
    return  "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: " + std::to_string(ResponseContent.length()) + "\r\n\r\n" + ResponseContent;

}