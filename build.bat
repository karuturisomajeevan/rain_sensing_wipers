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