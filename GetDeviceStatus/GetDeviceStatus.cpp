#include <memory>
#include <array>
#include <stdexcept>
#include "GetDeviceStatus.hpp"
// Function to execute shell commands
std::string DeviceStatus::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// Trim whitespace from both ends of a string
std::string DeviceStatus::trim(const std::string& s) {
    const auto start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    const auto end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

std::string DeviceStatus::GetBatteryPercentage() {
    std::string batteryPercentage = exec("acpi -b | grep -P -o '[0-9]+(?=%)'");
    return "Battery Percentage: " + trim(batteryPercentage) + "%";
}

std::string DeviceStatus::GetCPUUsage() {
    std::string cpuUsage = exec("top -bn1 | grep \"Cpu(s)\" | awk '{print $2 + $4}'");
    return "CPU Usage: " + trim(cpuUsage) + "%";
}

std::string DeviceStatus::GetRAMUsage() {
    std::string ramUsage = exec("free | grep Mem | awk '{print $3/$2 * 100.0}'");
    return "RAM Usage: " + trim(ramUsage) + "%";
}

std::string DeviceStatus::GetDiskUsage() {
    std::string diskUsage = exec("df -h | grep -vE '^Filesystem|tmpfs|cdrom' | awk '{ print $1 \": \" $5 }'");
    return "Disk Usage: " + trim(diskUsage);
}
