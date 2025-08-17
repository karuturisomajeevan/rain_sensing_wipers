# Rain-Sensing Wiper System - AI Recreation Prompts

## Overview
These prompts will allow you to recreate the exact same Rain-Sensing Wiper System project using any AI coding assistant. Follow these prompts in order for 100% accurate recreation.

---

## PROMPT 1: Project Initialization and Core Structure

```
Create a C++ Rain-Sensing Wiper System project with the following specifications:

PROJECT REQUIREMENTS:
- Language: C++11
- Platform: Windows (primary), cross-platform compatible
- Architecture: Object-oriented, modular design
- No external dependencies (self-contained)

CORE COMPONENTS NEEDED:
1. WindshieldWiperController - Main logic controller
2. RainSensor - Sensor data simulation and processing
3. WiperSystemManager - UI and system orchestration
4. WiperEnums - System enumerations and conversions
5. ColorUtilities - Console color output management
6. main.cpp - Application entry point

SYSTEM FEATURES:
- Two operating modes: AUTO (rain-sensing) and MANUAL (user control)
- Auto mode: Rain detection with 10-second turn-off delay
- Manual mode: Full wiper and spray control
- Real-time colored console output
- Comprehensive error handling

Create the basic project structure with empty header and source files for each component. Include appropriate header guards and basic class declarations.
```

---

## PROMPT 2: Enumerations and Basic Types

```
Implement the WiperEnums system with the following exact specifications:

CREATE WiperEnums.h with these enumerations:
1. WindshieldWiperSpeed enum class: OFF=0, LOW=1, MEDIUM=2, HIGH=3
2. OperatingMode enum class: MANUAL, AUTOMATIC  
3. WaterSprayMode enum class: OFF, LIGHT_SPRAY, HEAVY_SPRAY

CONVERSION FUNCTIONS NEEDED:
- convertWiperSpeedToString(WindshieldWiperSpeed) -> returns "OFF", "LOW", "MEDIUM", "HIGH"
- convertSprayModeToString(WaterSprayMode) -> returns "OFF", "LIGHT SPRAY", "HEAVY SPRAY"

CREATE WiperEnums.cpp with implementations of these conversion functions.

The conversion functions must return exact string matches as specified above.
```

---

## PROMPT 3: Color Utilities System

```
Create a ColorUtilities system for Windows console color output:

CREATE ColorUtilities.h with:
- Color constants: COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW, COLOR_CYAN, COLOR_WHITE, COLOR_GRAY
- Function: printColoredText(const std::string& text, const std::string& color)

CREATE ColorUtilities.cpp with:
- Windows-specific implementation using SetConsoleTextAttribute
- Color mapping: RED=12, GREEN=10, BLUE=9, YELLOW=14, CYAN=11, WHITE=15, GRAY=8
- Function to print text in specified color and reset to white afterward
- Include proper Windows headers: <windows.h>, <iostream>

The system should work on Windows console and gracefully handle other platforms by printing without color.
```

---

## PROMPT 4: Rain Sensor Implementation

```
Implement the RainSensor class with these exact specifications:

CREATE RainSensor.h with:
- SensorReadingData struct containing:
  - double lightPercentage (0.0-100.0)
  - bool isValidReading
  - bool isSuddenRainBurst  
  - bool isDewPresent
  - double dewLevel (0.0-100.0)

- RainSensor class with:
  - Constructor
  - readSensorData() method returning SensorReadingData
  - resetSensorFailureState() method

CREATE RainSensor.cpp with:
- Random sensor data generation (use <random>)
- Light percentage: random 0-100%
- Sudden rain burst: 15% chance when light < 30%
- Dew detection: 40% chance, level 50-95%
- Sensor failure: 5% chance (isValidReading = false)
- Realistic sensor behavior simulation

The sensor should generate varied, realistic data for testing the wiper system.
```

---

## PROMPT 5: Windshield Wiper Controller Core Logic

```
Implement WindshieldWiperController with these exact specifications:

CREATE WindshieldWiperController.h with:
- Private members:
  - WindshieldWiperSpeed currentWiperSpeed
  - OperatingMode currentOperatingMode  
  - WaterSprayMode currentWaterSprayMode
  - bool isWaitingToTurnOff
  - std::chrono::steady_clock::time_point turnOffStartTime
  - static const int TURN_OFF_DELAY_SECONDS = 10

- Public methods:
  - Constructor (initialize to OFF, AUTOMATIC, OFF, false)
  - mapLightPercentageToWiperSpeed(double lightPercentage) -> WindshieldWiperSpeed
  - setWiperSpeed(WindshieldWiperSpeed)
  - getCurrentWiperSpeed() const
  - setOperatingMode(OperatingMode)  
  - getCurrentOperatingMode() const
  - setWaterSprayMode(WaterSprayMode)
  - getCurrentWaterSprayMode() const
  - activateWaterSprayWithWiper(WaterSprayMode)
  - processAutomaticModeOperation(const RainSensor::SensorReadingData&)
  - isWaitingToTurnOffWipers() const
  - getRemainingTurnOffSeconds() const

MAPPING LOGIC for mapLightPercentageToWiperSpeed:
- >= 80.0% -> OFF
- >= 50.0% -> LOW  
- >= 20.0% -> MEDIUM
- < 20.0% -> HIGH

Include <chrono> header for timing functionality.
```

---

## PROMPT 6: Windshield Wiper Controller Implementation

```
Implement WindshieldWiperController.cpp with these exact behaviors:

CONSTRUCTOR:
- Initialize all members to default values (OFF, AUTOMATIC, OFF, false)

AUTOMATIC MODE PROCESSING (processAutomaticModeOperation):
1. If sensor invalid: set LOW speed (safety), cancel turn-off delay
2. If sudden rain burst: set HIGH speed immediately, cancel turn-off delay  
3. Normal operation:
   - Get target speed from mapLightPercentageToWiperSpeed
   - If target is OFF and current is not OFF:
     - Start 10-second countdown if not already waiting
     - Check if 10 seconds elapsed, then turn OFF
     - Keep current speed during countdown
   - If target is not OFF: set speed immediately, cancel countdown
   - If target is OFF and current is OFF: no delay needed

10-SECOND DELAY LOGIC:
- isWaitingToTurnOffWipers(): return isWaitingToTurnOff
- getRemainingTurnOffSeconds(): calculate remaining time from start time
- Countdown cancellation: reset isWaitingToTurnOff to false

SPRAY WITH WIPER (activateWaterSprayWithWiper):
- LIGHT_SPRAY -> set LOW wiper speed
- HEAVY_SPRAY -> set MEDIUM wiper speed

This is the critical component - the 10-second delay must work exactly as specified.
```

---

## PROMPT 7: System Manager - UI and Orchestration

```
Create WiperSystemManager class for UI and system orchestration:

CREATE WiperSystemManager.h with:
- Private members:
  - WindshieldWiperController wiperController
  - RainSensor rainDetectionSensor  
  - bool isSystemRunning

- Public methods:
  - Constructor
  - runSystem() - main system loop
  - initializeSystem() - setup and mode selection
  - selectInitialOperatingMode() -> OperatingMode
  - selectManualWiperSpeed() - manual speed selection menu
  - processUserInput() -> bool - handle keyboard input
  - getCurrentTimeString() -> std::string - format current time
  - logSystemEvent(const std::string&) - log with timestamp

REQUIRED INCLUDES:
- <iostream>, <iomanip>, <sstream>, <conio.h>, <windows.h>, <thread>
- All component headers

The class should handle all user interaction and coordinate between components.
```

---

## PROMPT 8: System Manager Implementation - User Input

```
Implement WiperSystemManager.cpp user input handling with these exact key mappings:

GLOBAL CONTROLS (work in any mode):
- 'm' or 'M': Switch to MANUAL mode, show speed selection menu
- 'a' or 'A': Switch to AUTO mode, clear any spray
- 'q' or 'Q': Quit system

MANUAL MODE ONLY CONTROLS:
- '0': Wiper OFF, clear spray, log "Manual: Wiper set to OFF (spray cleared)"
- '1': Wiper LOW, preserve spray, log "Manual: Wiper set to LOW (spray preserved)"  
- '2': Wiper MEDIUM, preserve spray, log "Manual: Wiper set to MEDIUM (spray preserved)"
- '3': Wiper HIGH, preserve spray, log "Manual: Wiper set to HIGH (spray preserved)"
- 's': Toggle light spray, log "Light spray activated/turned OFF (wipers continue)"
- 'S': Toggle heavy spray, log "Heavy spray activated/turned OFF (wipers continue)"  
- 'x' or 'X': Turn off spray only, log "Water spray turned OFF (wipers continue)"

KEY BEHAVIOR:
- Speed changes 1-3 preserve existing spray
- Only speed 0 clears spray
- Spray controls work independently of wiper speed
- Auto mode ignores all manual controls except mode switching

Use _kbhit() and _getch() for non-blocking input detection.
```

---

## PROMPT 9: System Manager Implementation - Display Logic

```
Implement WiperSystemManager.cpp display logic with these exact formats:

AUTO MODE DISPLAY:
- Format: "[HH:MM:SS] Mode: AUTO | Sensor: X% | Wiper: SPEED"
- Additional messages: "(Sudden Rain Burst)", "(Turning OFF in Xs)", "(Sensor Failure - Switch to Manual)"
- NO dew detection or spray information in auto mode
- Use separate display logic that bypasses normal displaySystemStatus

MANUAL MODE DISPLAY:  
- Format: "[HH:MM:SS] Mode: MANUAL | Wiper: SPEED"
- With spray: "[HH:MM:SS] Mode: MANUAL | Wiper: SPEED | Spray: SPRAY_TYPE"
- With dew: "[HH:MM:SS] Mode: MANUAL | Wiper: SPEED | Spray: SPRAY_TYPE (Dew Detected: X%)"

COLOR CODING:
- Timestamps: CYAN
- Mode AUTO: GREEN, Mode MANUAL: BLUE  
- Wiper OFF: GRAY, LOW: GREEN, MEDIUM: YELLOW, HIGH: RED
- Spray Light: CYAN, Heavy: BLUE
- Errors: RED, Warnings: YELLOW

TIME FORMAT:
- Use getCurrentTimeString() returning "HH:MM:SS" format
- Update display every 1000ms in main loop
- Check input every 50ms for responsiveness

The display must show clean auto mode (no dew/spray) vs full manual mode info.
```

---

## PROMPT 10: System Manager Implementation - Initialization

```
Implement WiperSystemManager.cpp initialization and main loop:

INITIALIZATION SEQUENCE:
1. Clear screen (system("cls"))
2. Show mode selection menu:
   "=== Rain-Sensing Wiper System Initialization ==="
   "Select operating mode:"
   "  1 - Manual Mode"  
   "  2 - Auto Mode (Rain Sensing)"
   "Enter your choice (1 or 2): "
3. Handle invalid input with retry
4. If manual mode selected, show speed selection menu
5. Clear screen and show startup message with selected mode
6. Display control instructions

MAIN SYSTEM LOOP (runSystem):
- Initialize system
- Run loop while isSystemRunning is true
- Process user input every 50ms  
- Update display every 1000ms
- In auto mode: read sensor data and process automatic operation
- In manual mode: display current status without sensor data
- Handle mode switching and state management

SPEED SELECTION MENU (selectManualWiperSpeed):
- Show options 0-3 with descriptions
- Handle invalid input with retry
- Set selected speed and return to main loop

The initialization must be user-friendly with clear instructions.
```

---

## PROMPT 11: Main Application Entry Point

```
Create main.cpp with the following exact implementation:

REQUIREMENTS:
- Include WiperSystemManager.h
- Simple main() function that creates WiperSystemManager instance
- Call runSystem() method
- Handle any exceptions gracefully
- Return 0 on success, 1 on error

EXACT CODE STRUCTURE:
```cpp
#include "WiperSystemManager.h"
#include <iostream>

int main() {
    try {
        WiperSystemManager wiperSystem;
        wiperSystem.runSystem();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "System error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown system error occurred" << std::endl;
        return 1;
    }
}
```

The main function should be minimal and delegate all functionality to WiperSystemManager.
```

---

## PROMPT 12: Build System and Compilation

```
Create build system files for the project:

CREATE build.bat (Windows batch file):
```batch
@echo off
echo Building Rain-Sensing Wiper System...
echo.

g++ -Wall -Wextra -Wpedantic -std=c++11 main.cpp ColorUtilities.cpp WiperEnums.cpp RainSensor.cpp WindshieldWiperController.cpp WiperSystemManager.cpp -o WiperSystemPureAuto.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Executable created: WiperSystemPureAuto.exe
    echo.
    echo To run the program, type: WiperSystemPureAuto.exe
) else (
    echo.
    echo Build failed! Please check for compilation errors.
)

pause
```

CREATE Makefile (cross-platform):
- Target: WiperSystemPureAuto
- Compiler: g++ with -Wall -Wextra -Wpedantic -std=c++11
- Sources: all .cpp files
- Clean target to remove build artifacts
- Run target to build and execute

The build system should compile with maximum warnings enabled and produce a working executable.
```

---

## PROMPT 13: Automated Test Suite

```
Create a comprehensive automated test suite:

CREATE AutomatedTests.cpp with:
- AutomatedTestSuite class with test tracking (totalTests, passedTests, failedTests)
- Test categories:
  1. System Initialization Tests (2 tests)
  2. Auto Mode Basic Tests (7 tests) 
  3. 10-Second Turn-Off Delay Tests (8 tests)
  4. Manual Mode Basic Tests (5 tests)
  5. Spray Functionality Tests (5 tests)
  6. Mode Switching Tests (3 tests)
  7. Edge Cases and Error Handling (4 tests)
  8. Enum Conversion Tests (9 tests)

CRITICAL TESTS TO IMPLEMENT:
- TC-006: Turn-off delay starts when conditions met
- TC-007: Countdown cancelled when rain detected  
- TC-009: Spray preservation during speed changes
- TC-012: Spray with wiper activation (dew removal)
- TC-015: Sensor failure handling

TEST OUTPUT FORMAT:
- Clean, human-readable format
- "[PASS]" or "[FAIL]" indicators
- Summary with statistics and pass rate
- No emojis or special characters

Each test should verify specific functionality and provide clear pass/fail results.
```

---

## PROMPT 14: Test Suite Implementation

```
Implement the automated test suite with these exact test cases:

SYSTEM INITIALIZATION TESTS:
- TC-001: Controller initializes with correct defaults (OFF, AUTOMATIC, OFF)
- TC-002: Rain sensor provides valid data structure (lightPercentage 0-100)

AUTO MODE BASIC TESTS:
- TC-003a-d: Light percentage mapping (90%->OFF, 60%->LOW, 30%->MEDIUM, 10%->HIGH)
- TC-004a-c: Boundary conditions (80%->OFF, 50%->LOW, 20%->MEDIUM)

10-SECOND TURN-OFF DELAY TESTS (CRITICAL):
- TC-005: Wipers activate with rain (30% -> MEDIUM)
- TC-006a: Turn-off delay starts when conditions met (85% triggers delay)
- TC-006b: Wipers remain on during delay
- TC-006c: Remaining time is reasonable (0-10 seconds)
- TC-007a: Countdown cancelled when rain detected (25% cancels delay)
- TC-007b: Wiper speed adjusts immediately after cancellation
- TC-008a: Sudden rain burst sets HIGH speed
- TC-008b: Sudden rain burst cancels any countdown

SPRAY FUNCTIONALITY TESTS:
- TC-011a-c: Basic spray controls (activate light, heavy, turn off)
- TC-012a-b: Spray with wiper activation (light->LOW, heavy->MEDIUM)

Create mock sensor data for testing and verify all behaviors match specifications exactly.
```

---

## PROMPT 15: Test Runner and Documentation

```
Create test execution system and documentation:

CREATE run_automated_tests.bat:
```batch
@echo off
echo ========================================
echo AUTOMATED TEST SUITE RUNNER  
echo ========================================
echo.

echo Compiling automated test suite...
g++ -Wall -Wextra -Wpedantic -std=c++11 AutomatedTests.cpp ColorUtilities.cpp WiperEnums.cpp RainSensor.cpp WindshieldWiperController.cpp -o AutomatedTests.exe

if %ERRORLEVEL% NEQ 0 (
    echo COMPILATION FAILED!
    echo Please check for compilation errors above.
    pause
    exit /b 1
)

echo Compilation successful!
echo.
echo Running automated tests...
echo.

AutomatedTests.exe

echo.
echo ========================================
echo Test execution completed!
echo ========================================
echo.

if exist AutomatedTests.exe (
    echo Cleaning up test executable...
    del AutomatedTests.exe
)

pause
```

CREATE README.md with:
- Project overview and features
- Build instructions for Windows and cross-platform
- Usage instructions with control mappings
- System requirements
- Expected behavior examples

The documentation should be comprehensive and professional.
```

---

## PROMPT 16: Final Integration and Validation

```
Perform final integration and create project summary:

INTEGRATION CHECKLIST:
1. Verify all files compile without warnings using -Wall -Wextra -Wpedantic
2. Test both build.bat and Makefile work correctly
3. Run automated test suite - all 43 tests must pass
4. Test manual execution of WiperSystemPureAuto.exe
5. Verify all features work as specified:
   - Auto mode with 10-second delay and countdown
   - Manual mode with spray preservation  
   - Mode switching with proper state management
   - Error handling for sensor failures

CREATE PROJECT_SUMMARY.md with:
- Project status and test results
- Complete feature list
- Technical architecture overview
- Usage instructions
- Quality metrics and assessments

FINAL VALIDATION:
- System must achieve 100% test pass rate
- All user requirements must be implemented
- Code must be production-ready quality
- Documentation must be complete

The final system should be a professional-grade application ready for deployment.
```

---

## PROMPT 17: Quality Assurance and Polish

```
Perform final quality assurance and polish:

CODE QUALITY REQUIREMENTS:
- Remove all emojis and special characters from all files
- Ensure consistent code formatting and style
- Add comprehensive comments to complex logic
- Verify all error handling is robust
- Check for memory leaks and resource management

TESTING REQUIREMENTS:
- All 43 automated tests must pass
- Manual testing of all user scenarios
- Edge case testing (rapid input, invalid input, sensor failures)
- Stress testing (extended operation, mode switching)

DOCUMENTATION REQUIREMENTS:
- Clean, professional documentation without emojis
- Clear build and usage instructions
- Complete feature documentation
- Technical architecture explanation

FINAL DELIVERABLES:
- Working executable (WiperSystemPureAuto.exe)
- Complete source code (8 .cpp/.h files)
- Build system (build.bat, Makefile, CMakeLists.txt)
- Automated test suite (AutomatedTests.cpp, run_automated_tests.bat)
- Documentation (README.md, PROJECT_SUMMARY.md)

The final product must be production-ready with professional quality standards.
```

---

## Usage Instructions for AI Recreation

### How to Use These Prompts:

1. **Sequential Execution**: Use prompts 1-17 in exact order
2. **Complete Each Step**: Ensure each prompt is fully implemented before proceeding
3. **Verify Output**: Test compilation and functionality after each major component
4. **Exact Specifications**: Follow all specifications precisely for 100% accuracy
5. **No Modifications**: Do not modify requirements unless explicitly needed for your platform

### Expected Results:

- **43 automated tests** all passing (100% success rate)
- **Production-ready executable** with all specified features
- **Complete documentation** and build system
- **Professional code quality** with no warnings or errors

### Validation:

After completing all prompts, you should have an identical Rain-Sensing Wiper System with:
- 10-second turn-off delay functionality
- Spray preservation in manual mode
- Clean auto mode (no dew/spray display)
- Comprehensive error handling
- Full test coverage

These prompts are designed to be 100% reproducible across different AI coding assistants.