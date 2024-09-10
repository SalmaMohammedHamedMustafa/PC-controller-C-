#ifndef FIRELINK_HPP
#define FIRELINK_HPP

#include <string>
#include <map>

class FireLink {
public:
    /*
    @brief: Opens the specified website in the default browser.
    @param url: The URL of the website to open.
    */
    void firefox(const std::string& url);

private:
    std::string GetUrl(const std::string& website);
    // Map of website names to URLs
    std::map<std::string, std::string> websites = {
        {"facebook", "https://www.facebook.com"},
        {"google", "https://www.google.com"},
        {"youtube", "https://www.youtube.com"},
        {"twitter", "https://www.twitter.com"}
    };
};

#endif // FIRELINK_HPP