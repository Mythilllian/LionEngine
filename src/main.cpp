#include <SDL.h>
#include "graphics/Renderer.hpp"
#include "graphics/ImageSprite.hpp"
#include "graphics/RectSprite.hpp"
#include "graphics/Color.hpp"
#include "assets/AssetManager.hpp"
#include "input/Input.hpp"
#include "scene/Entity.hpp"
#include <iostream>
using namespace GameEngine;
int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN);
    Renderer* renderer = new Renderer(window, Color::PINK, 100, 100);
    AssetManager assetManager("assets", renderer->getSDLRenderer());

    Texture* texture = assetManager.loadTextureAsset("images/face.png");

    Entity* rootEntity = new Entity(nullptr, "Root");
    Entity* childEntity = new Entity(rootEntity, "Child");
    Entity* grandChildEntity = new Entity(childEntity, "GrandChild");
    childEntity->localTransform.position = Vector2(0, 25);
    grandChildEntity->localTransform.position = Vector2(20, -15);
    std::cout << "Child global position: (" << childEntity->globalTransform().position.x << ", " << childEntity->globalTransform().position.y << ")" << std::endl;
    std::cout << "GrandChild global position: (" << grandChildEntity->globalTransform().position.x << ", " << grandChildEntity->globalTransform().position.y << ")" << std::endl;
    SpriteRenderer* sr1 = childEntity->addComponent<SpriteRenderer>();
    SpriteRenderer* sr2 = grandChildEntity->addComponent<SpriteRenderer>();
    //sr->sprite = new RectSprite(100, 50, Color(0, 255, 0), Color(255, 0, 0), 4, true);
    sr1->sprite = new ImageSprite(texture); // semi-transparent white tint
    sr1->layer = 0;
    sr2->sprite = new ImageSprite(texture, Color(255, 0, 0, 255)); // semi-transparent white tint
    sr2->layer = 1;
    childEntity->localTransform.scale = Vector2(16, 16);
    grandChildEntity->localTransform.scale = Vector2(0.5, 0.5);
    auto components = rootEntity->getComponentsInDescendants<SpriteRenderer>();
    std::cout << "Number of SpriteRenderer components in descendants: " << components.size() << std::endl;
    for(int i = 0; i < 30; i++){
        childEntity->localTransform.position.x++;
        renderer->render(components);
        SDL_Delay(1000);
    }

    SDL_DestroyWindow(window);

    // Input* input = new Input();

    // //ImageSprite* imageSprite = new ImageSprite(assetManager.loadTextureAsset("images/face.png"), Color(255, 255, 255, 128)); // semi-transparent white tint
    // RectSprite* rectSprite = new RectSprite(100, 50, Color(0, 255, 0), Color(255, 0, 0), 4, true);

    // //renderer->registerSprite(imageSprite);
    // renderer->registerSprite(rectSprite);

    // renderer->present();
    // SDL_Delay(3000);

    // while(true){
    //     if (input->isKeyPressed(87)) {
    //         std::cout << "W key pressed!" << std::endl;
    //         break;
    //     }
    //     renderer->present();
    //     SDL_Delay(16); // ~60 FPS
    // }
}