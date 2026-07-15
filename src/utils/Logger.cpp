#include "LionEngine/utils/Logger.hpp"

namespace LionEngine {
std::ofstream Logger::file;
std::string Logger::logDirectory = "logs";
std::string Logger::logFile = "log.txt";
bool Logger::outputToFile = false;
bool Logger::outputToConsole = true;
bool Logger::outputInfoToConsole = true;
bool Logger::outputWarningToConsole = true;
bool Logger::outputErrorToConsole = true;
bool Logger::timestampEnabled = true;

void Logger::logInfo(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log("[INFO]: " + formatLog(format, args), outputInfoToConsole);
    va_end(args);
}
void Logger::logWarning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log("[WARNING]: " + formatLog(format, args), outputWarningToConsole);
    va_end(args);
}
void Logger::logError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log("[ERROR]: " + formatLog(format, args), outputErrorToConsole);
    va_end(args);
}
void Logger::log(std::string message, bool typeOutputsToConsole) {
    if(timestampEnabled) {
        message = "[" + std::to_string(Time::elapsedTime()) + "s] " + message;
    }
    if (outputToConsole && typeOutputsToConsole) {
        std::cout << message << std::endl;
    }
    if (outputToFile) {
        if (!file.is_open()) {
            int i = 1;
            while(FileSystem::exists(logDirectory + "/" + logFile + std::to_string(i) + ".txt")) {
                i++;
            }
            file = FileSystem::openFileOutputStream(logDirectory + "/" + logFile + std::to_string(i) + ".txt");
        }
        file << message << std::endl;
    }
}
std::string Logger::formatLog(const char* format, va_list args)
{
    va_list copy;
    va_copy(copy, args);

    int size = vsnprintf(nullptr, 0, format, copy);
    va_end(copy);

    if (size < 0)
        return "";

    std::vector<char> buffer(size + 1);
    vsnprintf(buffer.data(), buffer.size(), format, args);

    return std::string(buffer.data(), size);
}
void Logger::closeLog() {
    if (file.is_open()) {
        file.close();
    }
}
}