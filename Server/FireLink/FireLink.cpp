#include "FireLink.hpp"
#include <cstdlib>

FireLink::FireLink() :
    facebook("https://www.facebook.com"),
    google("https://www.google.com"),
    youtube("https://www.youtube.com"),
    twitter("https://www.twitter.com") {}

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
        // Open the URL in the browser
        std::string openCommand = "firefox " + url;
        std::system(openCommand.c_str());

        // Bring the browser window to the front using xdotool
        std::string activateCommand = "xdotool search --name \"Firefox Web Browser\" windowactivate"; 
        std::system(activateCommand.c_str());
    #else
        #error Unsupported platform
    #endif
}
