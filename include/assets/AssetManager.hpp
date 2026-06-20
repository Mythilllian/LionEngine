#pragma once

#include <string>
#include <filesystem>
#include "assets/Asset.hpp"
#include "assets/Audio.hpp"
#include "assets/Music.hpp"

namespace GameEngine {
class AssetManager {
public:
    AssetManager(const std::string& assetDirectory) : assetDirectory(assetDirectory) {}
    Asset* loadAsset(const std::string& assetLocation);
    Audio* loadAudioAsset(const std::string& assetLocation, int volume = MIX_MAX_VOLUME);
    Music* loadMusicAsset(const std::string& assetLocation, int volume = MIX_MAX_VOLUME);
private:
    const std::string assetDirectory;
    bool exists(const std::string& location);
};
}