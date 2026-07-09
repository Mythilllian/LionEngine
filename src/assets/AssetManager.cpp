#include "assets/AssetManager.hpp"
#include <fstream>
#include "assets/Asset.hpp"
#include "assets/Audio.hpp"
#include "assets/Music.hpp"
#include "assets/Texture.hpp"
#include "graphics/Renderer.hpp"
#include "utils/Logger.hpp"

namespace GameEngine {
AssetManager::AssetManager(const std::string& assetDirectory, Renderer* renderer) : assetDirectory(assetDirectory), renderer(renderer) { }
Asset* AssetManager::loadAsset(const std::string& assetLocation) {
    if (!exists(assetLocation)) {
        Logger::logWarning("Asset file not found: %s", assetLocation.c_str());
        return nullptr;
    }
    return new Asset(assetDirectory + "/" + assetLocation);
}
json AssetManager::loadJson(const std::string& assetLocation) {
    if (!exists(assetLocation)) {
        Logger::logWarning("JSON file not found: %s", assetLocation.c_str());
        return nullptr;
    }
    std::ifstream file(assetDirectory + "/" + assetLocation);
    json j;
    file >> j;
    return j;
}
Audio* AssetManager::loadAudioAsset(const std::string& assetLocation, int volume) {
    if (!exists(assetLocation)) {
        Logger::logWarning("Audio file not found: %s", assetLocation.c_str());
        return nullptr;
    }
    return new Audio(assetDirectory + "/" + assetLocation, volume);
}
Music* AssetManager::loadMusicAsset(const std::string& assetLocation, int volume) {
    if (!exists(assetLocation)) {
        Logger::logWarning("Music file not found: %s", assetLocation.c_str());
        return nullptr;
    }
    return new Music(assetDirectory + "/" + assetLocation, volume);
}
Texture* AssetManager::loadTextureAsset(const std::string& assetLocation) {
    if (!exists(assetLocation)) {
        Logger::logWarning("Texture file not found: %s", assetLocation.c_str());
        return nullptr;
    }
    Texture* texture = new Texture(assetDirectory + "/" + assetLocation);
    texture->upload(*renderer);
    return texture;
}
void AssetManager::uploadUnloadedTextures() {
    for (Texture* texture : Texture::unloadedTextures) {
        texture->upload(*renderer);
    }
}
bool AssetManager::exists(const std::string& location) {
    std::ifstream file(assetDirectory + "/" + location);
    return file.good();
}
}