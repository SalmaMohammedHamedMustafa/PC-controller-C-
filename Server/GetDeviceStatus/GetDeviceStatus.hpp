#ifndef GETDEVICESTATUS_HPP
#define GETDEVICESTATUS_HPP

#include <string>
#include <map>
class DeviceStatus
{
    private:
    /*
    @brief: Execute a shell command and return the output.
    @param cmd: The command to execute.
    @return std::string: The output of the command.
    */
    std::string exec(const char* cmd);
    /*
    @brief: Trim whitespace from both ends of a string.
    @param s: The string to trim.
    */
    std::string trim(const std::string& s);
    // map of device status types to functions
    std::map<std::string, std::string (DeviceStatus::*)()> statusFunctions = {
        {"battery", &DeviceStatus::GetBatteryPercentage},
        {"cpu", &DeviceStatus::GetCPUUsage},
        {"ram", &DeviceStatus::GetRAMUsage},
        {"disk", &DeviceStatus::GetDiskUsage}
    };
    public:
    /*
    @brief: Get the status of the device.
    @param status: The status type to retrieve.
    @return std::string: The status of the device.
    */
    std::string GetDeviceStatus(const std::string& status);
    /*
    @brief: Get the battery percentage of the device.
    @return std::string: The battery percentage.
    */
    std::string GetBatteryPercentage();
    /*
    @brief: Get the CPU usage of the device.
    @return std::string: The CPU usage.
    */
    std::string GetCPUUsage();
    /*
    @brief: Get the RAM usage of the device.
    @return std::string: The RAM usage.
    */
    std::string GetRAMUsage();
    /*
    @brief: Get the disk usage of the device.
    @return std::string: The disk usage.
    */
    std::string GetDiskUsage();
};

#endif // GETDEVICESTATUS_HPP