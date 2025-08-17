#include "WiperSystemManager.h"
#include "ColorUtilities.h"

/**
 * @brief Main entry point for the Rain-Sensing Wiper System
 * @return Exit status code
 */
int main() {
    // Enable ANSI colors for Windows terminal
    enableAnsiColorSupport();
    
    // Create and run the wiper system
    WiperSystemManager wiperSystem;
    wiperSystem.runSystem();
    
    return 0;
}