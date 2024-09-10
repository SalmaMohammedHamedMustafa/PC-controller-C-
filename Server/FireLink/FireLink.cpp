#include "FireLink.hpp"
#include <cstdlib>
#include <string>

/*
@brief: Gets the URL of the specified website.
@param website: The name of the website.
@return std::string: The URL of the website.
*/
std::string FireLink::GetUrl(const std::string& website) {
    auto it = websites.find(website);
    if (it != websites.end()) {
        return it->second;
    } else {
        return "https://www.google.com";
    }
}

void FireLink::firefox(const std::string& website) {
    std::string url = GetUrl(website); // Get the URL of the website
    std::string command; // Command to open the URL in the browser

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
