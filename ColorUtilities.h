#ifndef COLOR_UTILITIES_H
#define COLOR_UTILITIES_H

#include <string>
#include <iostream>

// ANSI color codes for cross-platform terminal support
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_GRAY    "\033[90m"
#define COLOR_DEFAULT "\033[0m"

// Define the constant if not available
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

/**
 * @brief Enable ANSI color support in Windows terminal
 */
void enableAnsiColorSupport();

/**
 * @brief Print colored text to console
 * @param textMessage The text to print
 * @param colorCode The ANSI color code to use
 */
void printColoredText(const std::string& textMessage, const std::string& colorCode);

#endif // COLOR_UTILITIES_H