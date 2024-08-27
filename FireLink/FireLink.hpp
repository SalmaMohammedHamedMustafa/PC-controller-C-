#ifndef FIRELINK_HPP
#define FIRELINK_HPP

#include <string>

class FireLink {
public:
    FireLink();
    void firefox(const std::string& url);


    std::string facebook_link;
    std::string google_link;
    std::string youtube_link;
    std::string twitter_link;
};

#endif // FIRELINK_HPP