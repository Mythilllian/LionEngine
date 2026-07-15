#pragma once

#include "LionEngine/assets/Asset.hpp"
#include <SDL_mixer.h>
#include "LionEngine/utils/Logger.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace LionEngine {
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
void from_json(const json& j, Music& u);
void to_json(json& j, const Music& u);
}