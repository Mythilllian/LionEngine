#include "LionEngine/graphics/Sprite.hpp"

namespace LionEngine {
Sprite::Sprite(Color tintColor) : tint(tintColor) {}
float Sprite::calculateHeightFromWidth(float width) const {
    Vector2i size = getSize();
    return width * (static_cast<float>(size.y) / static_cast<float>(size.x));
}
void Sprite::serialize(json& j) const {
    j = json{{"visible", visible}, {"tint", tint}};
}
void Sprite::deserialize(const json& j) {
    if (j.contains("visible")) {
        visible = j.at("visible").get<bool>();
    }
    if (j.contains("tint")) {
        tint = j.at("tint").get<Color>();
    }
}
void from_json(const json& j, Sprite& u) {
    u.deserialize(j);
}
void to_json(json& j, const Sprite& u) {
    u.serialize(j);
}
}