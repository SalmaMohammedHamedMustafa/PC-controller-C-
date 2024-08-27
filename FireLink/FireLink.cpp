#include "FireLink.hpp"
#include <cstdlib>

FireLink::FireLink() :
    facebook_link("https://www.facebook.com"),
    google_link("https://www.google.com"),
    youtube_link("https://www.youtube.com"),
    twitter_link("https://www.twitter.com") {}

void FireLink::firefox(const std::string& url) {
    std::string command;
    #if defined(_WIN32)
    // Windows
    command = "start " + url;
    #elif defined(__APPLE__)
    // macOS
    command = "open " + url;
    #elif defined(__linux__)
    // Linux
    command = "xdg-open " + url;
    #else
    #error Unsupported platform
    #endif

    std::system(command.c_str());
}
