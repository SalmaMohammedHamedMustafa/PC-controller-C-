#ifndef FIRELINK_HPP
#define FIRELINK_HPP

#include <string>

class FireLink {
public:
    FireLink();
    void firefox(const std::string& url);


    std::string facebook;
    std::string google;
    std::string youtube;
    std::string twitter;
};

#endif // FIRELINK_HPP