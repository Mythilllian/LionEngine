#include "assets/AssetManager.hpp"
#include <fstream>

namespace GameEngine {
Asset* AssetManager::loadAsset(const std::string& assetLocation) {
    if (!exists(assetLocation)) {
        printf("Asset file not found: %s\n", assetLocation.c_str());
        return nullptr;
    }
    return new Asset(assetDirectory + "/" + assetLocation);
}
Audio* AssetManager::loadAudioAsset(const std::string& assetLocation, int volume) {
    if (!exists(assetLocation)) {
        printf("Audio file not found: %s\n", assetLocation.c_str());
        return nullptr;
    }
    return new Audio(assetDirectory + "/" + assetLocation, volume);
}
Music* AssetManager::loadMusicAsset(const std::string& assetLocation, int volume) {
    if (!exists(assetLocation)) {
        printf("Music file not found: %s\n", assetLocation.c_str());
        return nullptr;
    }
    return new Music(assetDirectory + "/" + assetLocation, volume);
}
bool AssetManager::exists(const std::string& location) {
    std::ifstream file(assetDirectory + "/" + location);
    return file.good();
}
}