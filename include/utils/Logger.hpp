#pragma once
#include <iostream>
#include <fstream>
#include <format>
#include <string>
#include <vector>
#include <cstdarg>
#include "core/Time.hpp"
#include "utils/FileSystem.hpp"

namespace GameEngine {
class Engine;
class Logger {
public:
    static std::string logDirectory;
    static std::string logFile;
    static bool outputToFile;
    static bool outputToConsole;
    static bool outputInfoToConsole;
    static bool outputWarningToConsole;
    static bool outputErrorToConsole;
    static bool timestampEnabled;
    static void logInfo(const char* format, ...);
    static void logError(const char* format, ...);
    static void logWarning(const char* format, ...);
    friend class Engine;
private:
    static std::ofstream file;
    static void createLog();
    static void log(std::string message, bool typeOutputsToConsole = true);
    static std::string formatLog(const char* format, va_list args);
    static void closeLog();
};
}