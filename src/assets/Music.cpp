#include "LionEngine/assets/Music.hpp"
#include <algorithm>

namespace LionEngine {
Music::Music(const std::string& path, int volume) : Asset(path), music(Mix_LoadMUS(path.c_str())) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    this->volume = volume;
    if (!music) {
        Logger::logWarning("Failed to load music: %s", Mix_GetError());
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
void from_json(const json& j, Music& u) {
    auto path = j.at("path").get<std::string>();
    auto volume = j.at("volume").get<int>();
    u.~Music();
    ::new (&u) Music(path, volume);
}
void to_json(json& j, const Music& u) {
    j = json{{"path", u.path}, {"volume", u.getVolume()}};
}
}