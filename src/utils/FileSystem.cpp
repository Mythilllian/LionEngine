#include "utils/FileSystem.hpp"

namespace GameEngine {
std::string FileSystem::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        printf("Failed to open file: %s\n", filePath.c_str());
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}
void FileSystem::writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        printf("Failed to open file for writing: %s\n", filePath.c_str());
        return;
    }
    file << content;
    file.close();
}
bool FileSystem::exists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}
}