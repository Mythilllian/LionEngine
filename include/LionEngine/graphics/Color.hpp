#pragma once

#include <SDL.h>
#include <nlohmann/json.hpp>
#include "LionEngine/math/Random.hpp"

namespace LionEngine {
class Color{
public:
    // Color values range from 0-255 (inclusive)
    Uint8 r, g, b, a;
    Color(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);
    Color toGrayscale();
    Color invert();
    SDL_Color toSDLColor() const;
    Color operator*(float scalar) const;
    Color operator*(const Color other) const;
    Color operator*(float scalar);
    Color operator*(const Color other);
    static Color random();
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color BLACK;
    static const Color WHITE;
    static const Color CYAN;
    static const Color DARK_GRAY;
    static const Color LIGHT_GRAY;
    static const Color MAGENTA;
    static const Color ORANGE;
    static const Color PINK;
    static const Color YELLOW;
};
void from_json(const nlohmann::json& j, Color& u);
void to_json(nlohmann::json& j, const Color& u);
}