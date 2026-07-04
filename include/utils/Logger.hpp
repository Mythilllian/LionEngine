#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace GameEngine {
class Logger {
public:
    static bool outputToFile;
    static bool outputToConsole;
    static void log(const std::string& message);
    static void logError(const std::string& message);
    static void logWarning(const std::string& message);
private:
    static std::ofstream file;
};
}