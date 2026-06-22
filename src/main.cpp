#include <SDL.h>
#include "graphics/Renderer.hpp"
#include "graphics/ImageSprite.hpp"
#include "graphics/RectSprite.hpp"
#include "graphics/Color.hpp"
#include "assets/AssetManager.hpp"
using namespace GameEngine;
int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    Renderer* renderer = new Renderer(window);
    AssetManager assetManager("assets", renderer->getSDLRenderer());

    //ImageSprite* imageSprite = new ImageSprite(assetManager.loadTextureAsset("images/face.png"), Color(255, 255, 255, 128)); // semi-transparent white tint
    RectSprite* rectSprite = new RectSprite(100, 50, Color(0, 255, 0), Color(255, 0, 0), 4, true);

    //renderer->registerSprite(imageSprite);
    renderer->registerSprite(rectSprite);

    renderer->present();
    SDL_Delay(3000);
}