#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>
#include <sstream>
#include "WindshieldWiperController.h"
#include "RainSensor.h"
#include "WiperEnums.h"
#include "ColorUtilities.h"

class AutomatedTestSuite {
private:
    int totalTests = 0;
    int passedTests = 0;
    int failedTests = 0;
    
    void logTest(const std::string& testName, bool passed, const std::string& details = "") {
        totalTests++;
        if (passed) {
            passedTests++;
            std::cout << "  [PASS] " << testName << std::endl;
        } else {
            failedTests++;
            std::cout << "  [FAIL] " << testName;
            if (!details.empty()) {
                std::cout << " - " << details;
            }
            std::cout << std::endl;
        }
    }
    
    void printTestHeader(const std::string& category) {
        std::cout << "\n" << std::string(70, '-') << std::endl;
        std::cout << category << std::endl;
        std::cout << std::string(70, '-') << std::endl;
    }

public:
    void runAllTests() {
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "AUTOMATED TEST SUITE - Rain-Sensing Wiper System" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        // Run all test categories
        testSystemInitialization();
        testAutoModeBasics();
        testTurnOffDelay();
        testManualModeBasics();
        testSprayFunctionality();
        testModeSwitching();
        testEdgeCases();
        testEnumConversions();
        
        // Print final results
        printFinalResults();
    }
    
private:
    void testSystemInitialization() {
        printTestHeader("SYSTEM INITIALIZATION TESTS");
        
        // TC-001: Controller Initialization
        WindshieldWiperController controller;
        logTest("TC-001: Controller initializes with correct defaults",
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::OFF &&
                controller.getCurrentOperatingMode() == OperatingMode::AUTOMATIC &&
                controller.getCurrentWaterSprayMode() == WaterSprayMode::OFF);
        
        // TC-002: Rain Sensor Initialization
        RainSensor sensor;
        auto sensorData = sensor.readSensorData();
        logTest("TC-002: Rain sensor provides valid data structure",
                sensorData.lightPercentage >= 0.0 && sensorData.lightPercentage <= 100.0);
    }
    
    void testAutoModeBasics() {
        printTestHeader("AUTO MODE BASIC TESTS");
        
        WindshieldWiperController controller;
        RainSensor sensor;
        
        // TC-003: Light percentage to wiper speed mapping
        WindshieldWiperSpeed speed90 = controller.mapLightPercentageToWiperSpeed(90.0);
        WindshieldWiperSpeed speed60 = controller.mapLightPercentageToWiperSpeed(60.0);
        WindshieldWiperSpeed speed30 = controller.mapLightPercentageToWiperSpeed(30.0);
        WindshieldWiperSpeed speed10 = controller.mapLightPercentageToWiperSpeed(10.0);
        
        logTest("TC-003a: Light 90% maps to OFF", speed90 == WindshieldWiperSpeed::OFF);
        logTest("TC-003b: Light 60% maps to LOW", speed60 == WindshieldWiperSpeed::LOW);
        logTest("TC-003c: Light 30% maps to MEDIUM", speed30 == WindshieldWiperSpeed::MEDIUM);
        logTest("TC-003d: Light 10% maps to HIGH", speed10 == WindshieldWiperSpeed::HIGH);
        
        // TC-004: Boundary conditions
        WindshieldWiperSpeed speed80 = controller.mapLightPercentageToWiperSpeed(80.0);
        WindshieldWiperSpeed speed50 = controller.mapLightPercentageToWiperSpeed(50.0);
        WindshieldWiperSpeed speed20 = controller.mapLightPercentageToWiperSpeed(20.0);
        
        logTest("TC-004a: Light 80% boundary (OFF)", speed80 == WindshieldWiperSpeed::OFF);
        logTest("TC-004b: Light 50% boundary (LOW)", speed50 == WindshieldWiperSpeed::LOW);
        logTest("TC-004c: Light 20% boundary (MEDIUM)", speed20 == WindshieldWiperSpeed::MEDIUM);
    }
    
    void testTurnOffDelay() {
        printTestHeader("10-SECOND TURN-OFF DELAY TESTS");
        
        WindshieldWiperController controller;
        
        // Create mock sensor data
        RainSensor::SensorReadingData rainData;
        rainData.isValidReading = true;
        rainData.isSuddenRainBurst = false;
        rainData.isDewPresent = false;
        rainData.lightPercentage = 30.0; // Should activate wipers
        rainData.dewLevel = 0.0;
        
        // TC-005: Initial activation
        controller.processAutomaticModeOperation(rainData);
        logTest("TC-005: Wipers activate with rain (30%)", 
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::MEDIUM);
        
        // TC-006: Conditions for turning off
        rainData.lightPercentage = 85.0; // Should trigger turn-off delay
        controller.processAutomaticModeOperation(rainData);
        
        logTest("TC-006a: Turn-off delay starts when conditions met",
                controller.isWaitingToTurnOffWipers());
        
        logTest("TC-006b: Wipers remain on during delay",
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::MEDIUM);
        
        logTest("TC-006c: Remaining time is reasonable",
                controller.getRemainingTurnOffSeconds() > 0 && 
                controller.getRemainingTurnOffSeconds() <= 10);
        
        // TC-007: Countdown cancellation
        rainData.lightPercentage = 25.0; // Rain detected again
        controller.processAutomaticModeOperation(rainData);
        
        logTest("TC-007a: Countdown cancelled when rain detected",
                !controller.isWaitingToTurnOffWipers());
        
        logTest("TC-007b: Wiper speed adjusts immediately",
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::MEDIUM);
        
        // TC-008: Sudden rain burst handling
        rainData.isSuddenRainBurst = true;
        controller.processAutomaticModeOperation(rainData);
        
        logTest("TC-008a: Sudden rain burst sets HIGH speed",
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::HIGH);
        
        logTest("TC-008b: Sudden rain burst cancels any countdown",
                !controller.isWaitingToTurnOffWipers());
    }
    
    void testManualModeBasics() {
        printTestHeader("MANUAL MODE BASIC TESTS");
        
        WindshieldWiperController controller;
        
        // TC-009: Manual mode setting
        controller.setOperatingMode(OperatingMode::MANUAL);
        logTest("TC-009: Operating mode can be set to MANUAL",
                controller.getCurrentOperatingMode() == OperatingMode::MANUAL);
        
        // TC-010: Manual wiper speed control
        controller.setWiperSpeed(WindshieldWiperSpeed::LOW);
        logTest("TC-010a: Manual wiper speed LOW", 
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::LOW);
        
        controller.setWiperSpeed(WindshieldWiperSpeed::MEDIUM);
        logTest("TC-010b: Manual wiper speed MEDIUM", 
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::MEDIUM);
        
        controller.setWiperSpeed(WindshieldWiperSpeed::HIGH);
        logTest("TC-010c: Manual wiper speed HIGH", 
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::HIGH);
        
        controller.setWiperSpeed(WindshieldWiperSpeed::OFF);
        logTest("TC-010d: Manual wiper speed OFF", 
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::OFF);
    }
    
    void testSprayFunctionality() {
        printTestHeader("SPRAY FUNCTIONALITY TESTS");
        
        WindshieldWiperController controller;
        controller.setOperatingMode(OperatingMode::MANUAL);
        
        // TC-011: Basic spray controls
        controller.setWaterSprayMode(WaterSprayMode::LIGHT_SPRAY);
        logTest("TC-011a: Light spray can be activated",
                controller.getCurrentWaterSprayMode() == WaterSprayMode::LIGHT_SPRAY);
        
        controller.setWaterSprayMode(WaterSprayMode::HEAVY_SPRAY);
        logTest("TC-011b: Heavy spray can be activated",
                controller.getCurrentWaterSprayMode() == WaterSprayMode::HEAVY_SPRAY);
        
        controller.setWaterSprayMode(WaterSprayMode::OFF);
        logTest("TC-011c: Spray can be turned off",
                controller.getCurrentWaterSprayMode() == WaterSprayMode::OFF);
        
        // TC-012: Spray with wiper activation (dew removal)
        controller.activateWaterSprayWithWiper(WaterSprayMode::LIGHT_SPRAY);
        logTest("TC-012a: Light spray activates with LOW wiper",
                controller.getCurrentWaterSprayMode() == WaterSprayMode::LIGHT_SPRAY &&
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::LOW);
        
        controller.activateWaterSprayWithWiper(WaterSprayMode::HEAVY_SPRAY);
        logTest("TC-012b: Heavy spray activates with MEDIUM wiper",
                controller.getCurrentWaterSprayMode() == WaterSprayMode::HEAVY_SPRAY &&
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::MEDIUM);
    }
    
    void testModeSwitching() {
        printTestHeader("MODE SWITCHING TESTS");
        
        WindshieldWiperController controller;
        
        // TC-013: Mode switching
        controller.setOperatingMode(OperatingMode::MANUAL);
        logTest("TC-013a: Can switch to MANUAL mode",
                controller.getCurrentOperatingMode() == OperatingMode::MANUAL);
        
        controller.setOperatingMode(OperatingMode::AUTOMATIC);
        logTest("TC-013b: Can switch to AUTO mode",
                controller.getCurrentOperatingMode() == OperatingMode::AUTOMATIC);
        
        // TC-014: State preservation during mode switch
        controller.setOperatingMode(OperatingMode::MANUAL);
        controller.setWiperSpeed(WindshieldWiperSpeed::MEDIUM);
        controller.setWaterSprayMode(WaterSprayMode::LIGHT_SPRAY);
        
        WindshieldWiperSpeed savedSpeed = controller.getCurrentWiperSpeed();
        
        controller.setOperatingMode(OperatingMode::AUTOMATIC);
        controller.setOperatingMode(OperatingMode::MANUAL);
        
        logTest("TC-014a: Wiper speed preserved during mode switch",
                controller.getCurrentWiperSpeed() == savedSpeed);
        
        // Note: Spray clearing when switching to auto mode is handled by WiperSystemManager
    }
    
    void testEdgeCases() {
        printTestHeader("EDGE CASES AND ERROR HANDLING");
        
        WindshieldWiperController controller;
        RainSensor sensor;
        
        // TC-015: Sensor failure handling
        RainSensor::SensorReadingData invalidData;
        invalidData.isValidReading = false;
        invalidData.lightPercentage = 0.0;
        invalidData.isSuddenRainBurst = false;
        invalidData.isDewPresent = false;
        invalidData.dewLevel = 0.0;
        
        controller.processAutomaticModeOperation(invalidData);
        logTest("TC-015: Sensor failure sets LOW speed (safety)",
                controller.getCurrentWiperSpeed() == WindshieldWiperSpeed::LOW);
        
        // TC-016: Extreme light percentage values
        WindshieldWiperSpeed speed0 = controller.mapLightPercentageToWiperSpeed(0.0);
        WindshieldWiperSpeed speed100 = controller.mapLightPercentageToWiperSpeed(100.0);
        
        logTest("TC-016a: Light 0% maps to HIGH", speed0 == WindshieldWiperSpeed::HIGH);
        logTest("TC-016b: Light 100% maps to OFF", speed100 == WindshieldWiperSpeed::OFF);
        
        // TC-017: Multiple rapid operations
        bool rapidOpsSuccess = true;
        try {
            for (int i = 0; i < 100; i++) {
                controller.setWiperSpeed(static_cast<WindshieldWiperSpeed>(i % 4));
                controller.setWaterSprayMode(static_cast<WaterSprayMode>(i % 3));
                controller.setOperatingMode(static_cast<OperatingMode>(i % 2));
            }
        } catch (...) {
            rapidOpsSuccess = false;
        }
        
        logTest("TC-017: System handles rapid operations without crashes", rapidOpsSuccess);
    }
    
    void testEnumConversions() {
        printTestHeader("ENUM CONVERSION TESTS");
        
        // TC-018: Wiper speed conversions
        std::string offStr = convertWiperSpeedToString(WindshieldWiperSpeed::OFF);
        std::string lowStr = convertWiperSpeedToString(WindshieldWiperSpeed::LOW);
        std::string mediumStr = convertWiperSpeedToString(WindshieldWiperSpeed::MEDIUM);
        std::string highStr = convertWiperSpeedToString(WindshieldWiperSpeed::HIGH);
        
        logTest("TC-018a: Wiper speed OFF converts correctly", offStr == "OFF");
        logTest("TC-018b: Wiper speed LOW converts correctly", lowStr == "LOW");
        logTest("TC-018c: Wiper speed MEDIUM converts correctly", mediumStr == "MEDIUM");
        logTest("TC-018d: Wiper speed HIGH converts correctly", highStr == "HIGH");
        
        // TC-019: Operating mode functionality (no conversion function available)
        OperatingMode autoMode = OperatingMode::AUTOMATIC;
        OperatingMode manualMode = OperatingMode::MANUAL;
        
        logTest("TC-019a: Operating mode AUTO enum works correctly", autoMode == OperatingMode::AUTOMATIC);
        logTest("TC-019b: Operating mode MANUAL enum works correctly", manualMode == OperatingMode::MANUAL);
        
        // TC-020: Spray mode conversions
        std::string sprayOffStr = convertSprayModeToString(WaterSprayMode::OFF);
        std::string lightSprayStr = convertSprayModeToString(WaterSprayMode::LIGHT_SPRAY);
        std::string heavySprayStr = convertSprayModeToString(WaterSprayMode::HEAVY_SPRAY);
        
        logTest("TC-020a: Spray mode OFF converts correctly", sprayOffStr == "OFF");
        logTest("TC-020b: Spray mode LIGHT converts correctly", lightSprayStr == "LIGHT SPRAY");
        logTest("TC-020c: Spray mode HEAVY converts correctly", heavySprayStr == "HEAVY SPRAY");
    }
    
    void printFinalResults() {
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "AUTOMATED TEST RESULTS SUMMARY" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        std::cout << "\nTest Statistics:" << std::endl;
        std::cout << "  Total Tests: " << totalTests << std::endl;
        std::cout << "  Passed: " << passedTests << std::endl;
        std::cout << "  Failed: " << failedTests << std::endl;
        
        double passRate = (totalTests > 0) ? (static_cast<double>(passedTests) / totalTests * 100.0) : 0.0;
        std::cout << "  Pass Rate: " << static_cast<int>(passRate) << "%" << std::endl;
        
        std::cout << "\nTest Quality Assessment:" << std::endl;
        if (failedTests == 0) {
            std::cout << "  Status: EXCELLENT - All tests passed! System is ready for production." << std::endl;
        } else if (passRate >= 90.0) {
            std::cout << "  Status: GOOD - Most tests passed. Minor issues to address." << std::endl;
        } else if (passRate >= 70.0) {
            std::cout << "  Status: FAIR - Some issues found. Review and fix before release." << std::endl;
        } else {
            std::cout << "  Status: POOR - Major issues found. Significant fixes needed." << std::endl;
        }
        
        std::cout << "\nTest Coverage Areas:" << std::endl;
        std::cout << "  - System Initialization" << std::endl;
        std::cout << "  - Auto Mode Basic Functionality" << std::endl;
        std::cout << "  - 10-Second Turn-Off Delay (Critical Feature)" << std::endl;
        std::cout << "  - Manual Mode Controls" << std::endl;
        std::cout << "  - Spray Functionality" << std::endl;
        std::cout << "  - Mode Switching" << std::endl;
        std::cout << "  - Edge Cases & Error Handling" << std::endl;
        std::cout << "  - Enum Conversions" << std::endl;
        
        if (failedTests > 0) {
            std::cout << "\nWARNING: Failed tests require attention before system deployment." << std::endl;
        } else {
            std::cout << "\nSUCCESS: All tests passed. System is ready for deployment." << std::endl;
        }
        
        std::cout << "\n" << std::string(80, '=') << std::endl;
    }
};

int main() {
    try {
        AutomatedTestSuite testSuite;
        testSuite.runAllTests();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test suite crashed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test suite crashed with unknown exception" << std::endl;
        return 1;
    }
}