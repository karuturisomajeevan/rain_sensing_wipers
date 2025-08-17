#include "WiperSystemManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include <thread>

WiperSystemManager::WiperSystemManager() : isSystemRunning(true) {
}

std::string WiperSystemManager::getCurrentTimeString() {
    auto currentTimePoint = std::chrono::system_clock::now();
    auto currentTimeValue = std::chrono::system_clock::to_time_t(currentTimePoint);
    auto timeStructure = *std::localtime(&currentTimeValue);
    
    std::ostringstream timeStringStream;
    timeStringStream << std::put_time(&timeStructure, "%H:%M:%S");
    return timeStringStream.str();
}

void WiperSystemManager::logSystemEvent(const std::string& eventMessage) {
    printColoredText("[" + getCurrentTimeString() + "] ", COLOR_CYAN);
    std::cout << eventMessage << std::endl;
}

void WiperSystemManager::displaySystemStatus(const RainSensor::SensorReadingData& sensorData, const std::string& alertMessage) {
    // Print timestamp in cyan color
    printColoredText("[" + getCurrentTimeString() + "] ", COLOR_CYAN);
    
    // Print current operating mode
    std::cout << "Mode: ";
    std::string operatingModeColor = (wiperController.getCurrentOperatingMode() == OperatingMode::AUTOMATIC) ? COLOR_GREEN : COLOR_BLUE;
    std::string operatingModeText = (wiperController.getCurrentOperatingMode() == OperatingMode::AUTOMATIC) ? "AUTO" : "MANUAL";
    printColoredText(operatingModeText, operatingModeColor);
    
    // Print sensor reading status
    std::cout << " | Sensor: ";
    if (!sensorData.isValidReading) {
        printColoredText("ERROR", COLOR_RED);
    } else {
        printColoredText(std::to_string(static_cast<int>(sensorData.lightPercentage)) + "%", COLOR_WHITE);
    }
    
    // Print current wiper speed
    std::cout << " | Wiper: ";
    
    // Color wiper status based on current speed
    std::string wiperSpeedColor;
    switch (wiperController.getCurrentWiperSpeed()) {
        case WindshieldWiperSpeed::OFF:
            wiperSpeedColor = COLOR_GRAY;
            break;
        case WindshieldWiperSpeed::LOW:
            wiperSpeedColor = COLOR_GREEN;
            break;
        case WindshieldWiperSpeed::MEDIUM:
            wiperSpeedColor = COLOR_YELLOW;
            break;
        case WindshieldWiperSpeed::HIGH:
            wiperSpeedColor = COLOR_RED;
            break;
    }
    printColoredText(convertWiperSpeedToString(wiperController.getCurrentWiperSpeed()), wiperSpeedColor);
    
    // Only show spray status in manual mode
    if (wiperController.getCurrentWaterSprayMode() != WaterSprayMode::OFF && wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
        std::cout << " | Spray: ";
        std::string sprayColor = (wiperController.getCurrentWaterSprayMode() == WaterSprayMode::HEAVY_SPRAY) ? COLOR_BLUE : COLOR_CYAN;
        printColoredText(convertSprayModeToString(wiperController.getCurrentWaterSprayMode()), sprayColor);
    }
    
    // Print special conditions and alerts
    if (sensorData.isSuddenRainBurst) {
        printColoredText(" (Sudden Rain Burst)", COLOR_RED);
    }
    
    // Only show dew detection in manual mode
    if (sensorData.isDewPresent && wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
        printColoredText(" (Dew Detected: " + std::to_string(static_cast<int>(sensorData.dewLevel)) + "%)", COLOR_MAGENTA);
    }
    
    if (!alertMessage.empty()) {
        printColoredText(" (" + alertMessage + ")", COLOR_RED);
    }
    
    std::cout << std::endl;
}

void WiperSystemManager::displayHelpInformation() {
    std::cout << "\n=== Rain-Sensing Wiper System ===" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  m - Switch to Manual Mode" << std::endl;
    std::cout << "  a - Switch to Auto Mode" << std::endl;
    std::cout << "  q - Quit simulation" << std::endl;
    std::cout << "\nManual Mode only:" << std::endl;
    std::cout << "  0 - OFF" << std::endl;
    std::cout << "  1 - LOW speed" << std::endl;
    std::cout << "  2 - MEDIUM speed" << std::endl;
    std::cout << "  3 - HIGH speed" << std::endl;
    std::cout << "\nSpray Controls (Manual Mode only):" << std::endl;
    std::cout << "  s - Toggle Light Spray" << std::endl;
    std::cout << "  S - Toggle Heavy Spray" << std::endl;
    std::cout << "  x - Turn OFF spray only" << std::endl;
    std::cout << "\nPress any key to continue..." << std::endl;
}

OperatingMode WiperSystemManager::selectInitialOperatingMode() {
    char userChoice;
    while (true) {
        printColoredText("\n=== Rain-Sensing Wiper System Initialization ===\n", COLOR_BLUE);
        std::cout << "Select operating mode:" << std::endl;
        printColoredText("  1 - Manual Mode\n", COLOR_GREEN);
        printColoredText("  2 - Auto Mode (Rain Sensing)\n", COLOR_GREEN);
        std::cout << "Enter your choice (1 or 2): ";
        
        userChoice = static_cast<char>(_getch());
        std::cout << userChoice << std::endl;
        
        if (userChoice == '1') {
            return OperatingMode::MANUAL;
        } else if (userChoice == '2') {
            return OperatingMode::AUTOMATIC;
        } else {
            std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
            Sleep(1000);
            system("cls");
        }
    }
}

void WiperSystemManager::selectManualWiperSpeed() {
    char userChoice;
    while (true) {
        printColoredText("\nManual Mode - Select wiper speed:\n", COLOR_BLUE);
        printColoredText("  0 - OFF (Default)\n", COLOR_GREEN);
        printColoredText("  1 - LOW speed\n", COLOR_GREEN);
        printColoredText("  2 - MEDIUM speed\n", COLOR_GREEN);
        printColoredText("  3 - HIGH speed\n", COLOR_GREEN);
        std::cout << "Enter your choice (0-3): ";
        
        userChoice = static_cast<char>(_getch());
        std::cout << userChoice << std::endl;
        
        switch (userChoice) {
            case '0':
                wiperController.setWiperSpeed(WindshieldWiperSpeed::OFF);
                wiperController.setWaterSprayMode(WaterSprayMode::OFF);
                logSystemEvent("Manual: Wiper set to OFF");
                return;
            case '1':
                wiperController.setWiperSpeed(WindshieldWiperSpeed::LOW);
                wiperController.setWaterSprayMode(WaterSprayMode::OFF);
                logSystemEvent("Manual: Wiper set to LOW");
                return;
            case '2':
                wiperController.setWiperSpeed(WindshieldWiperSpeed::MEDIUM);
                wiperController.setWaterSprayMode(WaterSprayMode::OFF);
                logSystemEvent("Manual: Wiper set to MEDIUM");
                return;
            case '3':
                wiperController.setWiperSpeed(WindshieldWiperSpeed::HIGH);
                wiperController.setWaterSprayMode(WaterSprayMode::OFF);
                logSystemEvent("Manual: Wiper set to HIGH");
                return;
            default:
                std::cout << "Invalid choice. Please enter 0, 1, 2, or 3." << std::endl;
                Sleep(1000);
        }
    }
}

bool WiperSystemManager::processUserInput() {
    if (_kbhit()) {
        char userInput = static_cast<char>(_getch());
        
        switch (userInput) {
            case 'm':
            case 'M':
                wiperController.setOperatingMode(OperatingMode::MANUAL);
                logSystemEvent("Switched to MANUAL mode");
                std::cout << std::endl;
                selectManualWiperSpeed();
                return true;
                
            case 'a':
            case 'A':
                wiperController.setOperatingMode(OperatingMode::AUTOMATIC);
                wiperController.setWaterSprayMode(WaterSprayMode::OFF); // Clear any spray when switching to auto
                rainDetectionSensor.resetSensorFailureState();
                logSystemEvent("Switched to AUTO mode (spray cleared)");
                return true;
                
            case 'q':
            case 'Q':
                isSystemRunning = false;
                return true;
                
            case '0':
                if (wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
                    wiperController.setWiperSpeed(WindshieldWiperSpeed::OFF);
                    wiperController.setWaterSprayMode(WaterSprayMode::OFF); // Turn off spray when wipers are OFF
                    logSystemEvent("Manual: Wiper set to OFF (spray cleared)");
                }
                return true;
                
            case '1':
                if (wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
                    wiperController.setWiperSpeed(WindshieldWiperSpeed::LOW);
                    // Keep current spray mode - don't change it
                    logSystemEvent("Manual: Wiper set to LOW (spray preserved)");
                }
                return true;
                
            case '2':
                if (wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
                    wiperController.setWiperSpeed(WindshieldWiperSpeed::MEDIUM);
                    // Keep current spray mode - don't change it
                    logSystemEvent("Manual: Wiper set to MEDIUM (spray preserved)");
                }
                return true;
                
            case '3':
                if (wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
                    wiperController.setWiperSpeed(WindshieldWiperSpeed::HIGH);
                    // Keep current spray mode - don't change it
                    logSystemEvent("Manual: Wiper set to HIGH (spray preserved)");
                }
                return true;
                
                            
            // Spray-only controls (work in manual mode only)
            case 's':
                if (wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
                    // Toggle light spray without changing wiper speed
                    if (wiperController.getCurrentWaterSprayMode() == WaterSprayMode::LIGHT_SPRAY) {
                        wiperController.setWaterSprayMode(WaterSprayMode::OFF);
                        logSystemEvent("Light spray turned OFF (wipers continue)");
                    } else {
                        wiperController.setWaterSprayMode(WaterSprayMode::LIGHT_SPRAY);
                        logSystemEvent("Light spray activated (wipers continue)");
                    }
                }
                return true;
                
            case 'S':
                if (wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
                    // Toggle heavy spray without changing wiper speed
                    if (wiperController.getCurrentWaterSprayMode() == WaterSprayMode::HEAVY_SPRAY) {
                        wiperController.setWaterSprayMode(WaterSprayMode::OFF);
                        logSystemEvent("Heavy spray turned OFF (wipers continue)");
                    } else {
                        wiperController.setWaterSprayMode(WaterSprayMode::HEAVY_SPRAY);
                        logSystemEvent("Heavy spray activated (wipers continue)");
                    }
                }
                return true;
                
            case 'x':
            case 'X':
                if (wiperController.getCurrentOperatingMode() == OperatingMode::MANUAL) {
                    // Turn off spray only, keep wipers running
                    wiperController.setWaterSprayMode(WaterSprayMode::OFF);
                    logSystemEvent("Water spray turned OFF (wipers continue)");
                }
                return true;
        }
    }
    return false;
}

void WiperSystemManager::initializeSystem() {
    system("cls");
    
    // Select initial operating mode
    OperatingMode initialOperatingMode = selectInitialOperatingMode();
    wiperController.setOperatingMode(initialOperatingMode);
    
    if (initialOperatingMode == OperatingMode::MANUAL) {
        selectManualWiperSpeed();
    }
    
    system("cls");
    printColoredText("Starting Rain-Sensing Wiper System...\n", COLOR_GREEN);
    std::cout << "Selected mode: ";
    std::string operatingModeColor = (initialOperatingMode == OperatingMode::AUTOMATIC) ? COLOR_GREEN : COLOR_BLUE;
    std::string operatingModeText = (initialOperatingMode == OperatingMode::AUTOMATIC) ? "AUTO" : "MANUAL";
    printColoredText(operatingModeText + "\n", operatingModeColor);
    printColoredText("Commands: 'm' (Manual), 'a' (Auto), 'q' (Quit)\n", COLOR_YELLOW);
    if (initialOperatingMode == OperatingMode::MANUAL) {
        printColoredText("Manual controls: 0 (OFF), 1 (LOW), 2 (MEDIUM), 3 (HIGH)\n", COLOR_YELLOW);
        printColoredText("Spray controls: 's' (Light), 'S' (Heavy), 'x' (OFF spray)\n", COLOR_CYAN);
    }
    std::cout << std::string(50, '-') << std::endl;
}

void WiperSystemManager::runSystem() {
    initializeSystem();
    
    auto lastStatusUpdateTime = std::chrono::steady_clock::now();
    const auto statusUpdateInterval = std::chrono::milliseconds(1000); // 1 second for status updates
    
    while (isSystemRunning) {
        // Check for user input frequently (every 50ms)
        processUserInput();
        
        if (!isSystemRunning) break;
        
        auto currentTime = std::chrono::steady_clock::now();
        
        // Only update status every second, but check input more frequently
        if (currentTime - lastStatusUpdateTime >= statusUpdateInterval) {
            if (wiperController.getCurrentOperatingMode() == OperatingMode::AUTOMATIC) {
                // Automatic mode - read sensor and process data
                auto currentSensorData = rainDetectionSensor.readSensorData();
                
                if (!currentSensorData.isValidReading) {
                    wiperController.processAutomaticModeOperation(currentSensorData);
                    // Auto mode simple display - no dew info
                    printColoredText("[" + getCurrentTimeString() + "] ", COLOR_CYAN);
                    printColoredText("Mode: AUTO", COLOR_GREEN);
                    std::cout << " | Sensor: ";
                    printColoredText("ERROR", COLOR_RED);
                    std::cout << " | Wiper: ";
                    std::string wiperSpeedColor = (wiperController.getCurrentWiperSpeed() == WindshieldWiperSpeed::HIGH) ? COLOR_RED : 
                                                 (wiperController.getCurrentWiperSpeed() == WindshieldWiperSpeed::MEDIUM) ? COLOR_YELLOW :
                                                 (wiperController.getCurrentWiperSpeed() == WindshieldWiperSpeed::LOW) ? COLOR_GREEN : COLOR_GRAY;
                    printColoredText(convertWiperSpeedToString(wiperController.getCurrentWiperSpeed()), wiperSpeedColor);
                    printColoredText(" (Sensor Failure - Switch to Manual)", COLOR_RED);
                    std::cout << std::endl;
                } else {
                    wiperController.processAutomaticModeOperation(currentSensorData);
                    // Auto mode simple display - only rain info, no dew
                    printColoredText("[" + getCurrentTimeString() + "] ", COLOR_CYAN);
                    printColoredText("Mode: AUTO", COLOR_GREEN);
                    std::cout << " | Sensor: ";
                    printColoredText(std::to_string(static_cast<int>(currentSensorData.lightPercentage)) + "%", COLOR_WHITE);
                    std::cout << " | Wiper: ";
                    std::string wiperSpeedColor = (wiperController.getCurrentWiperSpeed() == WindshieldWiperSpeed::HIGH) ? COLOR_RED : 
                                                 (wiperController.getCurrentWiperSpeed() == WindshieldWiperSpeed::MEDIUM) ? COLOR_YELLOW :
                                                 (wiperController.getCurrentWiperSpeed() == WindshieldWiperSpeed::LOW) ? COLOR_GREEN : COLOR_GRAY;
                    printColoredText(convertWiperSpeedToString(wiperController.getCurrentWiperSpeed()), wiperSpeedColor);
                    
                    // Only show sudden rain burst, no dew info
                    if (currentSensorData.isSuddenRainBurst) {
                        printColoredText(" (Sudden Rain Burst)", COLOR_RED);
                    }
                    
                    // Show countdown if waiting to turn off wipers
                    if (wiperController.isWaitingToTurnOffWipers()) {
                        int remainingSeconds = wiperController.getRemainingTurnOffSeconds();
                        printColoredText(" (Turning OFF in " + std::to_string(remainingSeconds) + "s)", COLOR_YELLOW);
                    }
                    
                    std::cout << std::endl;
                }
            } else {
                // Manual mode - display current status without sensor data
                std::string operatingModeString = "MANUAL";
                std::string wiperSpeedString = convertWiperSpeedToString(wiperController.getCurrentWiperSpeed());
                std::string statusMessage = "Mode: " + operatingModeString + " | Wiper: " + wiperSpeedString;
                
                // Add spray information if active
                if (wiperController.getCurrentWaterSprayMode() != WaterSprayMode::OFF) {
                    statusMessage += " | Spray: " + convertSprayModeToString(wiperController.getCurrentWaterSprayMode());
                }
                
                logSystemEvent(statusMessage);
            }
            
            lastStatusUpdateTime = currentTime;
        }
        
        // Short sleep to prevent excessive CPU usage while maintaining responsiveness
        Sleep(50); // Check input every 50ms
    }
    
    printColoredText("\nShutting down Rain-Sensing Wiper System...\n", COLOR_RED);
}