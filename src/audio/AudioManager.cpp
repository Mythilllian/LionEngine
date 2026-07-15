#include "LionEngine/audio/AudioManager.hpp"
#include <algorithm>

namespace LionEngine {
AudioManager::AudioManager() {
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Logger::logError("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
    }
}
AudioManager::~AudioManager() {
    Mix_CloseAudio();
}
void AudioManager::playMusic(const Music& music, int loops, int fadeInMs) {
    if (!music.getMusic()) {
        Logger::logWarning("Failed to load music: %s", Mix_GetError());
        return;
    }
    if (fadeInMs > 0) {
        Mix_FadeInMusic(music.getMusic(), loops, fadeInMs);
    } else {
        Mix_PlayMusic(music.getMusic(), loops);
    }
    musicDefaultVolumePercent = music.getVolumePercent();
    setMusicVolume();
}
int AudioManager::playAudio(const Audio& audio, int fadeInMs) {
    if (!audio.getAudioChunk()) {
        Logger::logWarning("Failed to load audio: %s", Mix_GetError());
        return -1;
    }
    if (fadeInMs > 0) {
        return Mix_FadeInChannel(-1, audio.getAudioChunk(), 0, fadeInMs);
    } else {
        return Mix_PlayChannel(-1, audio.getAudioChunk(), 0);
    }
}
void AudioManager::pauseMusic() {
    Mix_PauseMusic();
}
void AudioManager::resumeMusic() {
    Mix_ResumeMusic();
}
void AudioManager::stopMusic(int fadeOutMs) {
    if (fadeOutMs > 0) {
        Mix_FadeOutMusic(fadeOutMs);
    } else {
        Mix_HaltMusic();
    }
}
void AudioManager::pauseAudio(int channel) {
    Mix_Pause(channel);
}
void AudioManager::resumeAudio(int channel) {
    Mix_Resume(channel);
}
void AudioManager::stopAudio(int fadeOutMs) {
    if (fadeOutMs > 0) {
        Mix_FadeOutChannel(-1, fadeOutMs);
    } else {
        Mix_HaltChannel(-1);
    }
}
void AudioManager::stopAudioChannel(int channel, int fadeOutMs) {
    if (fadeOutMs > 0) {
        Mix_FadeOutChannel(channel, fadeOutMs);
    } else {
        Mix_HaltChannel(channel);
    }
}
void AudioManager::setMusicVolume(int volume) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    Mix_VolumeMusic(static_cast<int>(volume * getMasterVolumePercent() * musicDefaultVolumePercent));
}
void AudioManager::setAbsoluteMusicVolume(int volume) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    Mix_VolumeMusic(static_cast<int>(volume * musicDefaultVolumePercent));
}
void AudioManager::setMusicVolumePercent(float volume) {
    volume = std::clamp(volume, 0.0f, 1.0f);
    Mix_VolumeMusic(static_cast<int>(volume * MIX_MAX_VOLUME * getMasterVolumePercent() * musicDefaultVolumePercent));
}
void AudioManager::setAudioVolume(int volume, int channel) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    Mix_Volume(channel, static_cast<int>(volume * getMasterVolumePercent()));
}
void AudioManager::setAbsoluteAudioVolume(int volume, int channel) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    Mix_Volume(channel, static_cast<int>(volume));
}
void AudioManager::setAudioVolumePercent(float volume, int channel) {
    volume = std::clamp(volume, 0.0f, 1.0f);
    Mix_Volume(channel, static_cast<int>(volume * getMasterVolumePercent() * MIX_MAX_VOLUME));
}
void AudioManager::setMasterVolume(int volume) {
    volume = std::clamp(volume, 0, MIX_MAX_VOLUME);
    masterVolume = volume;
    setMusicVolume();
    Mix_Volume(-1, static_cast<int>(MIX_MAX_VOLUME * getMasterVolumePercent()));
}
int AudioManager::getMasterVolume() const {
    return masterVolume;
}
float AudioManager::getMasterVolumePercent() const {
    return masterVolume / static_cast<float>(MIX_MAX_VOLUME);
}
int AudioManager::getMusicVolume() const {
    if (musicDefaultVolumePercent == 0) return 0;
    if (masterVolume == 0) return 0;
    return static_cast<int>(Mix_VolumeMusic(-1) / getMasterVolumePercent());
}
int AudioManager::getAbsoluteMusicVolume() const {
    if (musicDefaultVolumePercent == 0) return 0;
    return static_cast<int>(Mix_VolumeMusic(-1) / musicDefaultVolumePercent);
}
float AudioManager::getMusicVolumePercent() const {
    if (musicDefaultVolumePercent == 0) return 0;
    if (masterVolume == 0) return 0;
    return Mix_VolumeMusic(-1) / (static_cast<float>(MIX_MAX_VOLUME) * getMasterVolumePercent() * musicDefaultVolumePercent);
}
int AudioManager::getAudioVolume(int channel) const {
    if (getMasterVolumePercent() == 0) return 0;
    return static_cast<int>(Mix_Volume(channel, -1) / getMasterVolumePercent());
}
int AudioManager::getAbsoluteAudioVolume(int channel) const {
    return Mix_Volume(channel, -1);
}
float AudioManager::getAudioVolumePercent(int channel) const {
    if (getMasterVolumePercent() == 0) return 0;
    return Mix_Volume(channel, -1) / (static_cast<float>(MIX_MAX_VOLUME) * getMasterVolumePercent());
}
}