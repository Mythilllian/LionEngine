#include "core/Engine.hpp"
#include "graphics/ImageSprite.hpp"
#include "graphics/RectSprite.hpp"
using namespace GameEngine;

int main(){
    Config config;
    config.windowSize = Vector2i(512, 448);
    config.windowTitle = "Game Engine";
    config.clearColor = Color::PINK;
    config.logicalSize = Vector2i(256, 224);
    config.targetFPS = 60;
    config.assetDirectory = "assets";
    Engine engine(config);

    Texture *texture = engine.assetManager().loadTextureAsset("images/face.png");

    Scene *scene = new Scene();
    Entity *entity = new Entity(scene->getRootEntity(), "Entity1");
    Entity *entity2 = new Entity(entity, "Child");
    entity->addComponent<SpriteRenderer>();
    entity->getComponent<SpriteRenderer>()->sprite = new ImageSprite(texture, Color::RED);
    entity->localTransform.scale = Vector2(16, 16);
    entity2->addComponent<SpriteRenderer>()->sprite = new RectSprite(Vector2(2,2));
    entity2->localTransform.position = Vector2(16, 16);
    engine.sceneManager().loadScene(scene);

    engine.run();
    return 0;
}