#include "LionEngine/core/PersistentData.hpp"

namespace LionEngine {
PersistentData::PersistentData(const json& initialData) : data(initialData) {}
PersistentData::PersistentData(const std::string& dataPath, const std::string& index) {
    if (!dataPath.empty()) {
        loadFromFile(dataPath, index);
    }
}
void PersistentData::saveToFile(const std::string& filename, const std::string& index) {
    std::string jsonString;
    if(!index.empty()) {
        jsonString = data[index].dump(4);
    } else {
        jsonString = data.dump(4);
    }
    FileSystem::writeFile(filename, jsonString);
}
void PersistentData::loadFromFile(const std::string& filename, const std::string& index) {
    if(index.empty()) {
        if (!FileSystem::exists(filename)) {
            data = json();
            return;
        }
        std::string jsonString = FileSystem::readFile(filename);
        data = json::parse(jsonString);
    } else {
        if (!FileSystem::exists(filename)) {
            data[index] = json();
            return;
        }
        std::string jsonString = FileSystem::readFile(filename);
        data[index] = json::parse(jsonString);
    }
}
}