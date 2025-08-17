#include "WindshieldWiperController.h"

WindshieldWiperController::WindshieldWiperController() 
    : currentWiperSpeed(WindshieldWiperSpeed::OFF), 
      currentOperatingMode(OperatingMode::AUTOMATIC),
      currentWaterSprayMode(WaterSprayMode::OFF),
      isWaitingToTurnOff(false) {
}

WindshieldWiperSpeed WindshieldWiperController::mapLightPercentageToWiperSpeed(double lightPercentage) {
    if (lightPercentage >= 80.0) {
        return WindshieldWiperSpeed::OFF;
    } else if (lightPercentage >= 50.0) {
        return WindshieldWiperSpeed::LOW;
    } else if (lightPercentage >= 20.0) {
        return WindshieldWiperSpeed::MEDIUM;
    } else {
        return WindshieldWiperSpeed::HIGH;
    }
}

void WindshieldWiperController::setWiperSpeed(WindshieldWiperSpeed newWiperSpeed) {
    currentWiperSpeed = newWiperSpeed;
}

WindshieldWiperSpeed WindshieldWiperController::getCurrentWiperSpeed() const {
    return currentWiperSpeed;
}

void WindshieldWiperController::setOperatingMode(OperatingMode newOperatingMode) {
    currentOperatingMode = newOperatingMode;
}

OperatingMode WindshieldWiperController::getCurrentOperatingMode() const {
    return currentOperatingMode;
}

void WindshieldWiperController::setWaterSprayMode(WaterSprayMode newSprayMode) {
    currentWaterSprayMode = newSprayMode;
}

WaterSprayMode WindshieldWiperController::getCurrentWaterSprayMode() const {
    return currentWaterSprayMode;
}

void WindshieldWiperController::activateWaterSprayWithWiper(WaterSprayMode sprayMode) {
    // Set spray mode and activate wipers for dew removal
    currentWaterSprayMode = sprayMode;
    
    // For dew removal, use appropriate wiper speed based on spray intensity
    if (sprayMode == WaterSprayMode::LIGHT_SPRAY) {
        currentWiperSpeed = WindshieldWiperSpeed::LOW;
    } else if (sprayMode == WaterSprayMode::HEAVY_SPRAY) {
        currentWiperSpeed = WindshieldWiperSpeed::MEDIUM;
    }
}

void WindshieldWiperController::processAutomaticModeOperation(const RainSensor::SensorReadingData& sensorData) {
    // Store current manual spray setting to preserve user choice
    WaterSprayMode userSprayMode = currentWaterSprayMode;
    
    if (!sensorData.isValidReading) {
        // Sensor failure - set to LOW speed as safety measure
        currentWiperSpeed = WindshieldWiperSpeed::LOW;
        isWaitingToTurnOff = false; // Cancel any pending turn-off
        // Keep user's spray setting in sensor failure
        return;
    }

    if (sensorData.isSuddenRainBurst) {
        // Sudden rain burst detected - immediately set to HIGH speed
        currentWiperSpeed = WindshieldWiperSpeed::HIGH;
        isWaitingToTurnOff = false; // Cancel any pending turn-off
        // Keep user's spray setting during rain burst
        currentWaterSprayMode = userSprayMode;
    } else {
        // Normal operation - map light percentage to appropriate wiper speed
        WindshieldWiperSpeed targetSpeed = mapLightPercentageToWiperSpeed(sensorData.lightPercentage);
        
        // Check if we should turn off wipers (target speed is OFF and wipers are currently on)
        if (targetSpeed == WindshieldWiperSpeed::OFF && currentWiperSpeed != WindshieldWiperSpeed::OFF) {
            if (!isWaitingToTurnOff) {
                // Start the 10-second countdown
                isWaitingToTurnOff = true;
                turnOffStartTime = std::chrono::steady_clock::now();
            } else {
                // Check if 10 seconds have passed
                auto currentTime = std::chrono::steady_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - turnOffStartTime);
                
                if (elapsedTime.count() >= TURN_OFF_DELAY_SECONDS) {
                    // 10 seconds have passed, turn off wipers
                    currentWiperSpeed = WindshieldWiperSpeed::OFF;
                    isWaitingToTurnOff = false;
                }
                // If 10 seconds haven't passed, keep current wiper speed
            }
        } else if (targetSpeed != WindshieldWiperSpeed::OFF) {
            // Rain detected again, cancel turn-off and set new speed immediately
            currentWiperSpeed = targetSpeed;
            isWaitingToTurnOff = false;
        } else {
            // Target speed is OFF and wipers are already OFF
            currentWiperSpeed = targetSpeed;
            isWaitingToTurnOff = false;
        }
        
        // Preserve user's manual spray setting (no automatic dew handling)
        currentWaterSprayMode = userSprayMode;
    }
}

bool WindshieldWiperController::isWaitingToTurnOffWipers() const {
    return isWaitingToTurnOff;
}

int WindshieldWiperController::getRemainingTurnOffSeconds() const {
    if (!isWaitingToTurnOff) {
        return 0;
    }
    
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - turnOffStartTime);
    int remainingSeconds = TURN_OFF_DELAY_SECONDS - static_cast<int>(elapsedTime.count());
    
    return (remainingSeconds > 0) ? remainingSeconds : 0;
}