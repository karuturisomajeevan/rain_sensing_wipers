#ifndef WIPER_ENUMS_H
#define WIPER_ENUMS_H

#include <string>

/**
 * @brief Enum for windshield wiper speeds
 */
enum class WindshieldWiperSpeed {
    OFF = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

/**
 * @brief Enum for system operating modes
 */
enum class OperatingMode {
    MANUAL,
    AUTOMATIC
};

/**
 * @brief Enum for water spray modes
 */
enum class WaterSprayMode {
    OFF,
    LIGHT_SPRAY,
    HEAVY_SPRAY
};

/**
 * @brief Convert WindshieldWiperSpeed to string representation
 * @param wiperSpeed The wiper speed to convert
 * @return String representation of the wiper speed
 */
std::string convertWiperSpeedToString(WindshieldWiperSpeed wiperSpeed);

/**
 * @brief Convert WaterSprayMode to string representation
 * @param sprayMode The spray mode to convert
 * @return String representation of the spray mode
 */
std::string convertSprayModeToString(WaterSprayMode sprayMode);

#endif // WIPER_ENUMS_H