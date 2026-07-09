#include "utils/FileSystem.hpp"

namespace GameEngine {
std::string FileSystem::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::logWarning("Failed to open file: %s", filePath.c_str());
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}
std::ofstream FileSystem::openFileOutputStream(const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::filesystem::path path(filePath);
        std::filesystem::create_directories(path.parent_path());
        file.open(filePath);
        if (file.fail()) {
            Logger::logWarning("Failed to open file for writing: %s", filePath.c_str());
            return std::ofstream();
        }
    }
    return file;
}
void FileSystem::writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file = openFileOutputStream(filePath);
    file << content;
    file.close();
}
bool FileSystem::exists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}
}