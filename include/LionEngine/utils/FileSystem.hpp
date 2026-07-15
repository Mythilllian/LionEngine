#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include "LionEngine/utils/Logger.hpp"

namespace LionEngine {
class FileSystem {
public:
    static std::string readFile(const std::string& filePath);
    static std::ofstream openFileOutputStream(const std::string& filePath);
    static void writeFile(const std::string& filePath, const std::string& content);
    static bool exists(const std::string& filePath);
};
}