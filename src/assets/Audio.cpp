#include "assets/Audio.hpp"
#include <algorithm>

namespace GameEngine {
Audio::Audio(const std::string& path, int volume) : Asset(path), audioChunk(Mix_LoadWAV(path.c_str())) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    this->volume = volume;
    if (audioChunk == nullptr) {
        printf("Failed to load audio: %s\n", Mix_GetError());
    } else {
        Mix_VolumeChunk(audioChunk, volume);
    }
}
Audio::~Audio() {
    if (audioChunk) {
        Mix_FreeChunk(audioChunk);
        audioChunk = nullptr;
    }
}
int Audio::setVolume(int volume) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    int oldVolume = this->volume;
    this->volume = volume;
    if (audioChunk) Mix_VolumeChunk(audioChunk, volume);
    return oldVolume;
}
float Audio::setVolumePercent(float volume) {
    volume = std::clamp(volume, 0.0f, 1.0f);
    float oldPercent = getVolumePercent();
    this->volume = static_cast<int>(volume * MIX_MAX_VOLUME);
    if (audioChunk) Mix_VolumeChunk(audioChunk, this->volume);
    return oldPercent;
}
int Audio::getVolume() const {
    return volume;
}
float Audio::getVolumePercent() const {
    return volume / static_cast<float>(MIX_MAX_VOLUME);
}
Mix_Chunk* Audio::getAudioChunk() const {
    return audioChunk;
}
}