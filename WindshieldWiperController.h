#ifndef WINDSHIELD_WIPER_CONTROLLER_H
#define WINDSHIELD_WIPER_CONTROLLER_H

#include "WiperEnums.h"
#include "RainSensor.h"
#include <chrono>

/**
 * @brief WindshieldWiperController class to handle wiper logic and control
 */
class WindshieldWiperController {
private:
    WindshieldWiperSpeed currentWiperSpeed;
    OperatingMode currentOperatingMode;
    WaterSprayMode currentWaterSprayMode;
    
    // Delay mechanism for turning off wipers
    bool isWaitingToTurnOff;
    std::chrono::steady_clock::time_point turnOffStartTime;
    static const int TURN_OFF_DELAY_SECONDS = 10;

public:
    /**
     * @brief Constructor for WindshieldWiperController
     */
    WindshieldWiperController();

    /**
     * @brief Map light percentage to appropriate wiper speed
     * @param lightPercentage The light percentage from sensor
     * @return Appropriate wiper speed for the given light percentage
     */
    WindshieldWiperSpeed mapLightPercentageToWiperSpeed(double lightPercentage);

    /**
     * @brief Set the wiper speed
     * @param newWiperSpeed The new wiper speed to set
     */
    void setWiperSpeed(WindshieldWiperSpeed newWiperSpeed);

    /**
     * @brief Get the current wiper speed
     * @return Current wiper speed
     */
    WindshieldWiperSpeed getCurrentWiperSpeed() const;

    /**
     * @brief Set the operating mode
     * @param newOperatingMode The new operating mode to set
     */
    void setOperatingMode(OperatingMode newOperatingMode);

    /**
     * @brief Get the current operating mode
     * @return Current operating mode
     */
    OperatingMode getCurrentOperatingMode() const;

    /**
     * @brief Set the water spray mode
     * @param newSprayMode The new water spray mode to set
     */
    void setWaterSprayMode(WaterSprayMode newSprayMode);

    /**
     * @brief Get the current water spray mode
     * @return Current water spray mode
     */
    WaterSprayMode getCurrentWaterSprayMode() const;

    /**
     * @brief Activate water spray with wiper for dew removal
     * @param sprayMode The spray intensity to use
     */
    void activateWaterSprayWithWiper(WaterSprayMode sprayMode);

    /**
     * @brief Process automatic mode operation based on sensor data
     * @param sensorData The sensor data to process
     */
    void processAutomaticModeOperation(const RainSensor::SensorReadingData& sensorData);

    /**
     * @brief Check if the system is waiting to turn off wipers
     * @return True if waiting to turn off, false otherwise
     */
    bool isWaitingToTurnOffWipers() const;

    /**
     * @brief Get remaining seconds before turning off wipers
     * @return Remaining seconds, or 0 if not waiting
     */
    int getRemainingTurnOffSeconds() const;
};

#endif // WINDSHIELD_WIPER_CONTROLLER_H