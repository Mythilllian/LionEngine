#include "core/Engine.hpp"
#include "ecs/ImageSpriteRenderer.hpp"
#include "ecs/RectSpriteRenderer.hpp"
#include "utils/FileSystem.hpp"
#include <nlohmann/json.hpp>
using namespace GameEngine;
using json = nlohmann::json;

int main(){
    Config config = json::parse(FileSystem::readFile("config/config.json"));
    Engine engine(config);

    if(config.startupScenePath == ""){
        Texture *texture = engine.assetManager().loadTextureAsset("images/face.png");

        Scene *scene = new Scene();
        Entity *entity = new Entity(scene->getRootEntity(), "Entity1");
        Entity *entity2 = new Entity(entity, "Child");
        entity->addComponent<ImageSpriteRenderer>();
        entity->getComponent<ImageSpriteRenderer>()->sprite = new ImageSprite(texture, Color::RED);
        entity->localTransform.scale = Vector2(16, 16);
        entity2->addComponent<RectSpriteRenderer>()->sprite = new RectSprite(Vector2(2,2));
        entity2->localTransform.position = Vector2(16, 16);
        engine.sceneManager().loadScene(scene);
        Logger::logInfo("Texture path: %s", texture->path.c_str());

        json currentSceneJson = engine.sceneManager().getCurrentScene();
        FileSystem::writeFile("assets/scenes/scene1.json", currentSceneJson.dump(4));
    }

    engine.run();
    return 0;
}