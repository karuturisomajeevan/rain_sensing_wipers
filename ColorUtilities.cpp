#include "ColorUtilities.h"
#include <windows.h>

void enableAnsiColorSupport() {
    #ifdef _WIN32
    HANDLE consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode = 0;
    GetConsoleMode(consoleOutputHandle, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(consoleOutputHandle, consoleMode);
    #endif
}

void printColoredText(const std::string& textMessage, const std::string& colorCode) {
    std::cout << colorCode << textMessage << COLOR_RESET;
}