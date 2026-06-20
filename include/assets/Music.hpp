#pragma once

#include "assets/Asset.hpp"
#include <SDL_mixer.h>

namespace GameEngine {
class Music : public Asset {
public:
    Music(const std::string& path, int volume = MIX_MAX_VOLUME);
    ~Music() override;
    int setVolume(int volume); // volume: 0-128
    float setVolumePercent(float volume); // volume: 0.0-1.0
    int getVolume() const;
    float getVolumePercent() const;
    Mix_Music* getMusic() const;
private:
    Mix_Music* music;
    int volume; // default/maximum volume of the music
};
}