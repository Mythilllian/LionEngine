#pragma once

#include <string>
#include <filesystem>
#include "assets/Asset.hpp"
#include "assets/Audio.hpp"
#include "assets/Music.hpp"
#include "assets/Texture.hpp"
#include <SDL.h>

namespace GameEngine {
class AssetManager {
public:
    AssetManager(const std::string& assetDirectory, SDL_Renderer* renderer) : assetDirectory(assetDirectory), renderer(renderer) {}
    Asset* loadAsset(const std::string& assetLocation);
    Audio* loadAudioAsset(const std::string& assetLocation, int volume = MIX_MAX_VOLUME);
    Music* loadMusicAsset(const std::string& assetLocation, int volume = MIX_MAX_VOLUME);
    Texture* loadTextureAsset(const std::string& assetLocation);
private:
    const std::string assetDirectory;
    SDL_Renderer* renderer;
    bool exists(const std::string& location);
};
}