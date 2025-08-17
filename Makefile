# Makefile for Rain-Sensing Wiper System

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++11
TARGET = WiperSystemPureAuto
SOURCES = main.cpp ColorUtilities.cpp WiperEnums.cpp RainSensor.cpp WindshieldWiperController.cpp WiperSystemManager.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = ColorUtilities.h WiperEnums.h RainSensor.h WindshieldWiperController.h WiperSystemManager.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	del /Q *.o $(TARGET).exe 2>nul || true

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install dependencies (if needed)
install:
	@echo "No external dependencies required"

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  run     - Build and run the program"
	@echo "  help    - Show this help message"

# Declare phony targets
.PHONY: all clean run install help