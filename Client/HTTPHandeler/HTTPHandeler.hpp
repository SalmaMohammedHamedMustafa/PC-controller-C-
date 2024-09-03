#ifndef HTTP_HANDELER_HPP
#define HTTP_HANDELER_HPP

#include <string>

class HTTPHandeler {
public:
    /*
    @brief: Parses the client request to extract the message body.
    @param request: The client request string.
    @return std::string: The message body extracted from the request.
    */
    std::string ParseRequest(const std::string& request);
    /*
    @brief: Creates an HTTP response message with the given content.
    @param ResponseContent: The content to include in the response message.
    @return std::string: The HTTP response message.
    */
    std::string CreateResponse(const std::string& ResponseContent);
};

#endif // HTTP_HANDELER_HPP