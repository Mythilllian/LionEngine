#include <SDL.h>
#include "assets/AssetManager.hpp"
#include "audio/AudioManager.hpp"
int main() {
    SDL_Init(SDL_INIT_VIDEO);

    GameEngine::AssetManager assetManager("assets");
    GameEngine::AudioManager audioManager;

    GameEngine::Music* music = assetManager.loadMusicAsset("background.mp3");
    GameEngine::Audio* audio = assetManager.loadAudioAsset("sound.wav");
    
    // audioManager.playMusic(*music);
    audioManager.playAudio(*audio);
    SDL_Delay(3000);
    audioManager.playAudio(*audio, 500);
    SDL_Delay(3000);
    int x = audioManager.playAudio(*audio);
    audioManager.setAudioVolume(50);
    SDL_Delay(3000);
    audioManager.playAudio(*audio, 500);
    SDL_Delay(5000);
    // audioManager.pauseMusic();
    // SDL_Delay(2000);
    // audioManager.resumeMusic();
    // int x = audioManager.playAudio(*audio,500);
    // SDL_Delay(5000);
    // audioManager.stopMusic(1000);
    SDL_Quit();
    return 0;
}