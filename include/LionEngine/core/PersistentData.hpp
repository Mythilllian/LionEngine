#pragma once

#include <nlohmann/json.hpp>
#include "LionEngine/utils/FileSystem.hpp"

using json = nlohmann::json;

namespace LionEngine {
class PersistentData {
public:
    json data;
    PersistentData(const json& initialData = json());
    PersistentData(const std::string& dataPath, const std::string& index = "");
    void saveToFile(const std::string& filename, const std::string& index = "");
    void loadFromFile(const std::string& filename, const std::string& index = "");
};
}