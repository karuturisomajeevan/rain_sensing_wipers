# Rain-Sensing Wiper System - Project Structure

## File Organization

This project has been modularized into separate files for better maintainability, readability, and professional code organization.

### Core Files

#### 1. **main.cpp**
- **Purpose**: Entry point of the application
- **Contents**: Main function that initializes and runs the system
- **Dependencies**: WiperSystemManager.h, ColorUtilities.h

#### 2. **ColorUtilities.h / ColorUtilities.cpp**
- **Purpose**: Handle console color output functionality
- **Contents**: 
  - ANSI color code definitions
  - Functions for enabling color support
  - Colored text printing utilities
- **Key Functions**:
  - `enableAnsiColorSupport()`: Enable ANSI colors in Windows terminal
  - `printColoredText()`: Print text with specified color

#### 3. **WiperEnums.h / WiperEnums.cpp**
- **Purpose**: Define enumerations and related utility functions
- **Contents**:
  - `WindshieldWiperSpeed` enum (OFF, LOW, MEDIUM, HIGH)
  - `OperatingMode` enum (MANUAL, AUTOMATIC)
  - `convertWiperSpeedToString()`: Convert enum to string representation

#### 4. **RainSensor.h / RainSensor.cpp**
- **Purpose**: Simulate rain detection sensor functionality
- **Contents**:
  - `RainSensor` class with sensor simulation logic
  - `SensorReadingData` structure for sensor data
  - Random number generation for sensor readings
  - Sensor failure simulation
  - Sudden rain burst detection
- **Key Methods**:
  - `readSensorData()`: Get current sensor reading
  - `resetSensorFailureState()`: Reset sensor failure condition

#### 5. **WindshieldWiperController.h / WindshieldWiperController.cpp**
- **Purpose**: Control wiper speed and operating modes
- **Contents**:
  - `WindshieldWiperController` class
  - Logic for mapping sensor data to wiper speeds
  - Mode switching functionality
  - Automatic mode processing
- **Key Methods**:
  - `mapLightPercentageToWiperSpeed()`: Convert sensor data to wiper speed
  - `processAutomaticModeOperation()`: Handle automatic mode logic
  - Getters and setters for speed and mode

#### 6. **WiperSystemManager.h / WiperSystemManager.cpp**
- **Purpose**: Manage overall system operation and user interface
- **Contents**:
  - `WiperSystemManager` class
  - User interface and menu handling
  - System status display
  - Input processing
  - Main system loop
- **Key Methods**:
  - `initializeSystem()`: System initialization
  - `runSystem()`: Main system loop
  - `displaySystemStatus()`: Show current status
  - `processUserInput()`: Handle user commands

### Build Files

#### 7. **Makefile**
- **Purpose**: Build automation using Make
- **Targets**:
  - `all`: Build the project (default)
  - `clean`: Remove build artifacts
  - `run`: Build and run the program
  - `help`: Show available targets

#### 8. **CMakeLists.txt**
- **Purpose**: Build automation using CMake
- **Features**:
  - Cross-platform build support
  - Automatic dependency handling
  - Installation rules
  - Custom run target

### Documentation

#### 9. **README.md**
- **Purpose**: Project overview and usage instructions
- **Contents**: Features, installation, usage guide, troubleshooting

#### 10. **PROJECT_STRUCTURE.md** (this file)
- **Purpose**: Detailed project structure documentation
- **Contents**: File organization, dependencies, build instructions

## Dependencies Graph

```
main.cpp
├── WiperSystemManager.h
│   ├── RainSensor.h
│   ├── WindshieldWiperController.h
│   │   ├── WiperEnums.h
│   │   └── RainSensor.h
│   ├── ColorUtilities.h
│   └── WiperEnums.h
└── ColorUtilities.h
```

## Class Relationships

```
WiperSystemManager
├── Contains: RainSensor (composition)
├── Contains: WindshieldWiperController (composition)
├── Uses: ColorUtilities (utility functions)
└── Uses: WiperEnums (data types)

WindshieldWiperController
├── Uses: WiperEnums (data types)
└── Uses: RainSensor::SensorReadingData (parameter)

RainSensor
└── Defines: SensorReadingData (nested struct)
```

## Build Instructions

### Using Make (Windows/Linux/macOS)
```bash
# Build the project
make

# Clean build artifacts
make clean

# Build and run
make run

# Show help
make help
```

### Using CMake (Cross-platform)
```bash
# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
cmake --build .

# Run the program
./bin/RainSensingWiperSystem
```

### Manual Compilation
```bash
g++ -Wall -Wextra -Wpedantic -std=c++11 \
    main.cpp ColorUtilities.cpp WiperEnums.cpp \
    RainSensor.cpp WindshieldWiperController.cpp \
    WiperSystemManager.cpp -o WiperSystem
```

## Code Organization Benefits

1. **Modularity**: Each class has its own files
2. **Maintainability**: Easy to modify individual components
3. **Reusability**: Components can be reused in other projects
4. **Testability**: Individual classes can be unit tested
5. **Readability**: Clear separation of concerns
6. **Professional Structure**: Follows industry standards
7. **Scalability**: Easy to add new features
8. **Documentation**: Each file has clear purpose and documentation

## Naming Conventions

- **Files**: PascalCase for classes (e.g., `RainSensor.h`)
- **Classes**: PascalCase (e.g., `WindshieldWiperController`)
- **Functions**: camelCase (e.g., `getCurrentWiperSpeed`)
- **Variables**: camelCase (e.g., `currentWiperSpeed`)
- **Constants**: UPPER_CASE (e.g., `COLOR_RED`)
- **Enums**: PascalCase (e.g., `WindshieldWiperSpeed`)

This modular structure makes the codebase professional, maintainable, and easy to understand for any developer working on the project.