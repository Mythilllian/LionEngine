#pragma once

#include <string>
#include "utils/FileSystem.hpp"
#include "assets/Asset.hpp"
#include "assets/Audio.hpp"
#include "assets/Music.hpp"
#include "assets/Texture.hpp"
#include "graphics/Renderer.hpp"

namespace GameEngine {
class AssetManager {
public:
    AssetManager(const std::string& assetDirectory, Renderer* renderer);
    ~AssetManager() = default;
    Asset* loadAsset(const std::string& assetLocation);
    Audio* loadAudioAsset(const std::string& assetLocation, int volume = MIX_MAX_VOLUME);
    Music* loadMusicAsset(const std::string& assetLocation, int volume = MIX_MAX_VOLUME);
    Texture* loadTextureAsset(const std::string& assetLocation);
    bool exists(const std::string& location);
private:
    const std::string assetDirectory;
    Renderer* renderer;
};
}