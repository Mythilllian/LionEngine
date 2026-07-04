#pragma once
#include <string>
#include <fstream>

namespace GameEngine {
class FileSystem {
public:
    static std::string readFile(const std::string& filePath);
    static void writeFile(const std::string& filePath, const std::string& content);
    static bool exists(const std::string& filePath);
};
}