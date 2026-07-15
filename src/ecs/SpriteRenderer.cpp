#include "LionEngine/ecs/SpriteRenderer.hpp"

namespace LionEngine {
SpriteRenderer::SpriteRenderer(Entity* parent) : Component(parent), sprite(nullptr), layer(0) 
{
    SERIALIZEFIELD(layer);
    SERIALIZEFIELD(resizeToEntity);
    SERIALIZEFIELD(keepAspectRatio);
}
}