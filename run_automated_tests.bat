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