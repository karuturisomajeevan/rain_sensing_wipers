#include "WiperEnums.h"

std::string convertWiperSpeedToString(WindshieldWiperSpeed wiperSpeed) {
    switch (wiperSpeed) {
        case WindshieldWiperSpeed::OFF: return "OFF";
        case WindshieldWiperSpeed::LOW: return "LOW";
        case WindshieldWiperSpeed::MEDIUM: return "MEDIUM";
        case WindshieldWiperSpeed::HIGH: return "HIGH";
        default: return "UNKNOWN";
    }
}

std::string convertSprayModeToString(WaterSprayMode sprayMode) {
    switch (sprayMode) {
        case WaterSprayMode::OFF: return "OFF";
        case WaterSprayMode::LIGHT_SPRAY: return "LIGHT SPRAY";
        case WaterSprayMode::HEAVY_SPRAY: return "HEAVY SPRAY";
        default: return "UNKNOWN";
    }
}