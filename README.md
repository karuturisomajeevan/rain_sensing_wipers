# Rain-Sensing Wiper System

A comprehensive C++ simulation of an intelligent rain-sensing windshield wiper system with real-time sensor monitoring, automatic speed adjustment, and colorized console output.

## Features

### Core Functionality
- **Dual Operating Modes**: Manual and Automatic operation
- **Real-time Rain Sensing**: Simulated light sensor with percentage-based readings
- **Intelligent Speed Control**: Automatic wiper speed adjustment based on rain intensity
- **Sensor Failure Detection**: Handles sensor malfunctions gracefully
- **Sudden Rain Burst Detection**: Immediate response to heavy rainfall
- **Interactive Controls**: Real-time user input without blocking system operation

### Visual Features
- **Colorized Output**: Professional color-coded console display
- **Real-time Status Updates**: Live system monitoring with timestamps
- **Intuitive Menus**: Easy-to-navigate initialization and control interfaces
- **Visual Feedback**: Color-coded wiper speeds and system states

## System Requirements

- **Operating System**: Windows (uses Windows Console API for colors)
- **Compiler**: GCC/MinGW with C++11 support or later
- **Dependencies**: Standard C++ libraries, Windows API

## Installation & Compilation

### Prerequisites
```bash
# Ensure you have GCC/MinGW installed
gcc --version
```

### Compilation
```bash
# Standard compilation
g++ -Wall -Wextra -Wpedantic main.cpp -o main.exe

# With additional warnings (recommended for development)
g++ -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion main.cpp -o main.exe
```

### Running the Program
```bash
./main.exe
```

## Usage Guide

### Initial Setup
1. **Launch the program** - The system will display an initialization menu
2. **Select Operating Mode**:
   - Press `1` for Manual Mode
   - Press `2` for Auto Mode (Rain Sensing)
3. **Manual Mode Setup** (if selected):
   - Choose initial wiper speed (0-3)

### Runtime Controls

#### Universal Commands
- `m` or `M` - Switch to Manual Mode
- `a` or `A` - Switch to Auto Mode  
- `q` or `Q` - Quit the simulation

#### Manual Mode Controls
- `0` - Set wiper to OFF
- `1` - Set wiper to LOW speed
- `2` - Set wiper to MEDIUM speed
- `3` - Set wiper to HIGH speed

### Operating Modes

#### Auto Mode
- **Sensor Monitoring**: Continuously reads simulated rain sensor
- **Automatic Speed Adjustment**: 
  - 80-100% light → OFF
  - 50-79% light → LOW
  - 20-49% light → MEDIUM
  - 0-19% light → HIGH
- **Sudden Rain Detection**: Immediate HIGH speed activation
- **Sensor Failure Handling**: Defaults to LOW speed on sensor error

#### Manual Mode
- **User Control**: Complete manual control over wiper speed
- **Status Monitoring**: Displays current wiper setting
- **Instant Response**: Immediate speed changes via keyboard input

## Color Scheme

### Status Display Colors
| Element | Color | Meaning |
|---------|-------|---------|
| Timestamps | Cyan | System time markers |
| AUTO Mode | Green | Automatic operation |
| MANUAL Mode | Blue | Manual operation |
| Sensor Values | White | Valid readings |
| Sensor ERROR | Red | Sensor malfunction |
| OFF Speed | Gray | Wipers disabled |
| LOW Speed | Green | Low intensity |
| MEDIUM Speed | Yellow | Medium intensity |
| HIGH Speed | Red | High intensity |
| Alerts/Warnings | Red | Critical notifications |
| Menu Headers | Blue | Navigation elements |
| Menu Options | Green | Available choices |
| Commands | Yellow | User instructions |

## Technical Architecture

### Class Structure

#### `Sensor` Class
- **Purpose**: Simulates rain sensor hardware
- **Features**: 
  - Random light percentage generation
  - Sensor failure simulation (1% chance)
  - Sudden rain burst detection (>30% drop)
- **Data Structure**: `SensorData` with validity and burst flags

#### `WiperController` Class
- **Purpose**: Manages wiper speed and system mode
- **Features**:
  - Speed mapping algorithms
  - Mode switching capabilities
  - Auto mode processing logic

#### `SystemManager` Class
- **Purpose**: Orchestrates entire system operation
- **Features**:
  - User interface management
  - Real-time input processing
  - Status display and logging
  - Color management

### Key Algorithms

#### Rain Intensity Mapping
```cpp
if (lightPercentage >= 80.0) return WiperSpeed::OFF;
else if (lightPercentage >= 50.0) return WiperSpeed::LOW;
else if (lightPercentage >= 20.0) return WiperSpeed::MEDIUM;
else return WiperSpeed::HIGH;
```

#### Sudden Rain Detection
```cpp
bool isSuddenBurst = (lastReading - newReading) > 30.0;
```

## Code Quality Features

- **Warning-Free Compilation**: Compiles cleanly with strict warning flags
- **Type Safety**: Proper static casting for type conversions
- **Memory Safety**: No dynamic memory allocation, stack-based design
- **Exception Safety**: Robust error handling for sensor failures
- **Modern C++**: Uses C++11 features like `enum class` and `auto`

## Development Notes

### Compilation Warnings Resolved
- Fixed conversion warnings for `_getch()` return values
- Resolved random number generator initialization warnings  
- Eliminated variable shadowing issues
- Proper type casting throughout codebase

### Performance Optimizations
- Non-blocking input processing (50ms polling)
- Efficient status update intervals (1-second updates)
- Minimal CPU usage during idle periods

## Future Enhancements

### Potential Features
- **Configuration File**: Save/load user preferences
- **Data Logging**: Export sensor data and system events
- **Network Integration**: Remote monitoring capabilities
- **Advanced Sensors**: Multiple sensor types (humidity, temperature)
- **Maintenance Alerts**: Wiper blade replacement notifications
- **Weather Integration**: Real weather data integration

### Cross-Platform Support
- **Linux/macOS**: ANSI color code implementation
- **Terminal Detection**: Automatic color capability detection
- **Configuration Options**: Disable colors for unsupported terminals

## Troubleshooting

### Common Issues

#### Colors Not Displaying
- **Cause**: Terminal doesn't support Windows Console API
- **Solution**: Use Windows Command Prompt or PowerShell

#### Compilation Errors
- **Missing Headers**: Ensure `<windows.h>` and `<conio.h>` are available
- **Compiler Version**: Use GCC 4.8+ or equivalent with C++11 support

#### Input Not Responsive
- **Cause**: Terminal input buffering
- **Solution**: Use Windows-compatible terminal

## License

This project is provided as-is for educational and demonstration purposes.

## Author

Rain-Sensing Wiper System - A comprehensive automotive simulation project demonstrating real-time system control, sensor integration, and user interface design in C++.

---

**Version**: 1.0  
**Last Updated**: 2024  
**Compatibility**: Windows with GCC/MinGW