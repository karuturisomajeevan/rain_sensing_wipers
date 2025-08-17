#ifndef WIPER_SYSTEM_MANAGER_H
#define WIPER_SYSTEM_MANAGER_H

#include "RainSensor.h"
#include "WindshieldWiperController.h"
#include "ColorUtilities.h"
#include "WiperEnums.h"
#include <string>
#include <chrono>

/**
 * @brief WiperSystemManager class to manage the overall wiper system operation
 */
class WiperSystemManager {
private:
    RainSensor rainDetectionSensor;
    WindshieldWiperController wiperController;
    bool isSystemRunning;

    /**
     * @brief Get current time as formatted string
     * @return Current time in HH:MM:SS format
     */
    std::string getCurrentTimeString();

    /**
     * @brief Log system event with timestamp
     * @param eventMessage The message to log
     */
    void logSystemEvent(const std::string& eventMessage);

    /**
     * @brief Display current system status
     * @param sensorData Current sensor data
     * @param alertMessage Optional alert message to display
     */
    void displaySystemStatus(const RainSensor::SensorReadingData& sensorData, const std::string& alertMessage = "");

    /**
     * @brief Display help information
     */
    void displayHelpInformation();

    /**
     * @brief Select initial operating mode
     * @return Selected operating mode
     */
    OperatingMode selectInitialOperatingMode();

    /**
     * @brief Select manual wiper speed
     */
    void selectManualWiperSpeed();

    /**
     * @brief Process user input
     * @return True if input was processed, false otherwise
     */
    bool processUserInput();

public:
    /**
     * @brief Constructor for WiperSystemManager
     */
    WiperSystemManager();

    /**
     * @brief Initialize the wiper system
     */
    void initializeSystem();

    /**
     * @brief Run the wiper system main loop
     */
    void runSystem();
};

#endif // WIPER_SYSTEM_MANAGER_H