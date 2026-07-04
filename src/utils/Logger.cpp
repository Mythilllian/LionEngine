#include "utils/Logger.hpp"

namespace GameEngine {
std::ofstream Logger::file;
bool Logger::outputToFile = false;
bool Logger::outputToConsole = true;
void Logger::log(const std::string& message) {
    if (outputToConsole) {
        std::cout << "[INFO]: " << message << std::endl;
    }
    if (outputToFile) {
        if (!file.is_open()) {
            file.open("log.txt", std::ios::app);
        }
        file << "[INFO]: " << message << std::endl;
    }
}
void Logger::logError(const std::string& message) {
    if (outputToConsole) {
        std::cerr << "[ERROR]: " << message << std::endl;
    }
    if (outputToFile) {
        if (!file.is_open()) {
            file.open("log.txt", std::ios::app);
        }
        file << "[ERROR]: " << message << std::endl;
    }
}
void Logger::logWarning(const std::string& message) {
    if (outputToConsole) {
        std::cout << "[WARNING]: " << message << std::endl;
    }
    if (outputToFile) {
        if (!file.is_open()) {
            file.open("log.txt", std::ios::app);
        }
        file << "[WARNING]: " << message << std::endl;
    }
}
}