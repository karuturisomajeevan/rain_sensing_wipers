#ifndef RAIN_SENSOR_H
#define RAIN_SENSOR_H

#include <random>
#include <chrono>

/**
 * @brief RainSensor class to simulate rain detection sensor
 */
class RainSensor {
private:
    std::mt19937 randomNumberGenerator;
    std::uniform_real_distribution<double> lightPercentageDistribution;
    std::uniform_real_distribution<double> sensorFailureDistribution;
    std::uniform_real_distribution<double> dewLevelDistribution;
    double previousSensorReading;
    bool isSensorInFailureState;

public:
    /**
     * @brief Constructor for RainSensor
     */
    RainSensor();

    /**
     * @brief Structure to hold sensor reading data
     */
    struct SensorReadingData {
        double lightPercentage;
        bool isValidReading;
        bool isSuddenRainBurst;
        bool isDewPresent;
        double dewLevel;
    };

    /**
     * @brief Read current sensor data
     * @return SensorReadingData containing current sensor information
     */
    SensorReadingData readSensorData();

    /**
     * @brief Reset sensor failure state
     */
    void resetSensorFailureState();
};

#endif // RAIN_SENSOR_H