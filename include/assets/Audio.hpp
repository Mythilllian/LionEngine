#pragma once

#include "assets/Asset.hpp"
#include <SDL_mixer.h>

namespace GameEngine {
class Audio : public Asset {
public:
    Audio(const std::string& path, int volume);
    ~Audio() override;
    int setVolume(int volume); // volume: 0-128
    float setVolumePercent(float volume); // volume: 0.0-1.0
    int getVolume() const;
    float getVolumePercent() const;
    Mix_Chunk* getAudioChunk() const;
private:
    Mix_Chunk* audioChunk;
    int volume; // default/maximum volume of the audio
};
}