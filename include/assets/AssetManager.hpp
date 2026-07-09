#pragma once

#include <string>
#include "utils/FileSystem.hpp"
#include <SDL_mixer.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace GameEngine {
class Asset;
class Audio;
class Music;
class Texture;
class Renderer;
class AssetManager {
public:
    AssetManager(const std::string& assetDirectory, Renderer* renderer);
    ~AssetManager() = default;
    Asset* loadAsset(const std::string& assetLocation);
    json loadJson(const std::string& assetLocation);
    Audio* loadAudioAsset(const std::string& assetLocation, int volume = MIX_MAX_VOLUME);
    Music* loadMusicAsset(const std::string& assetLocation, int volume = MIX_MAX_VOLUME);
    Texture* loadTextureAsset(const std::string& assetLocation);
    void uploadUnloadedTextures();
    bool exists(const std::string& location);
private:
    const std::string assetDirectory;
    Renderer* renderer;
};
}