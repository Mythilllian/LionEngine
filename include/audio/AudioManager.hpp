#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include "assets/Audio.hpp"
#include "assets/Music.hpp"


namespace GameEngine {
class AudioManager {
public:
    AudioManager();
    ~AudioManager();
    int playAudio(const Audio& audio, int fadeInMs = 0); // returns the channel the audio is playing on, or -1 on error
    void playMusic(const Music& music, int loops = 0, int fadeInMs = 0); // loops: 0 = play once, -1 = loop indefinitely
    void pauseMusic();
    void resumeMusic();
    void stopMusic(int fadeOutMs = 0);
    void pauseAudio(int channel = -1); // pause specific channel or all channels if channel == -1
    void resumeAudio(int channel = -1); // resume specific channel or all channels if channel == -1
    void stopAudio(int fadeOutMs = 0);
    void stopAudioChannel(int channel, int fadeOutMs = 0);
    void setMusicVolume(int volume = MIX_MAX_VOLUME); // volume: 0-128
    void setAbsoluteMusicVolume(int volume = MIX_MAX_VOLUME); // volume: 0-128, sets music volume without master volume applied
    void setMusicVolumePercent(float volume = 1.0f); // volume: 0.0-1.0
    void setAudioVolume(int volume = MIX_MAX_VOLUME, int channel = -1); // volume: 0-128, sets all audio channels
    void setAbsoluteAudioVolume(int volume = MIX_MAX_VOLUME, int channel = -1); // volume: 0-128, sets audio volume without master volume applied
    void setAudioVolumePercent(float volume = 1.0f, int channel = -1); // volume: 0.0-1.0, sets all audio channels
    void setMasterVolume(int volume = MIX_MAX_VOLUME); // volume: 0-128, sets both music and audio volume
    int getMasterVolume() const;
    float getMasterVolumePercent() const;
    int getMusicVolume() const;
    int getAbsoluteMusicVolume() const;
    float getMusicVolumePercent() const;
    int getAudioVolume(int channel = -1) const;
    int getAbsoluteAudioVolume(int channel = -1) const;
    float getAudioVolumePercent(int channel = -1) const;
private:
    int masterVolume = MIX_MAX_VOLUME; // default/maximum volume for both music and audio
    float musicDefaultVolumePercent = 1.0f;
};
}