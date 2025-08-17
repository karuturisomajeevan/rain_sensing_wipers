#include "RainSensor.h"

RainSensor::RainSensor() 
    : randomNumberGenerator(static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())),
      lightPercentageDistribution(0.0, 100.0),
      sensorFailureDistribution(0.0, 1.0),
      dewLevelDistribution(0.0, 100.0),
      previousSensorReading(95.0),
      isSensorInFailureState(false) {
}

RainSensor::SensorReadingData RainSensor::readSensorData() {
    SensorReadingData currentSensorData;
    
    // Simulate sensor failure (1% chance)
    if (sensorFailureDistribution(randomNumberGenerator) < 0.01) {
        isSensorInFailureState = true;
    }

    if (isSensorInFailureState) {
        currentSensorData.lightPercentage = -1; // Invalid reading
        currentSensorData.isValidReading = false;
        currentSensorData.isSuddenRainBurst = false;
        currentSensorData.isDewPresent = false;
        currentSensorData.dewLevel = 0.0;
        return currentSensorData;
    }

    // Generate new sensor reading
    double currentSensorReading = lightPercentageDistribution(randomNumberGenerator);
    
    // Generate dew level reading
    double currentDewLevel = dewLevelDistribution(randomNumberGenerator);
    
    // Check for sudden rain burst (drop > 30%)
    currentSensorData.isSuddenRainBurst = (previousSensorReading - currentSensorReading) > 30.0;
    
    // Check for dew presence (dew level > 60% indicates dew formation)
    currentSensorData.isDewPresent = (currentDewLevel > 60.0);
    currentSensorData.dewLevel = currentDewLevel;
    
    currentSensorData.lightPercentage = currentSensorReading;
    currentSensorData.isValidReading = (currentSensorReading >= 0.0 && currentSensorReading <= 100.0);
    
    previousSensorReading = currentSensorReading;
    return currentSensorData;
}

void RainSensor::resetSensorFailureState() {
    isSensorInFailureState = false;
}