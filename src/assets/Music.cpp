#include "assets/Music.hpp"
#include <algorithm>

namespace GameEngine {
Music::Music(const std::string& path, int volume) : Asset(path), music(Mix_LoadMUS(path.c_str())) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    this->volume = volume;
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
    }
}
Music::~Music() {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}
int Music::setVolume(int volume) {
    int oldVolume = this->volume;
    this->volume = volume;
    return oldVolume;
}
float Music::setVolumePercent(float volume) {
    volume = std::clamp(volume, 0.0f, 1.0f);
    float oldVolume = getVolumePercent();
    this->volume = static_cast<int>(volume * MIX_MAX_VOLUME);
    return oldVolume;
}
int Music::getVolume() const {
    return volume;
}
float Music::getVolumePercent() const {
    return volume / static_cast<float>(MIX_MAX_VOLUME);
}
Mix_Music* Music::getMusic() const {
    return music;
}
}