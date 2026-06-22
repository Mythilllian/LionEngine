#pragma once

#include <SDL.h>

namespace GameEngine {
class Color{
public:
    // Color values range from 0-255 (inclusive)
    Uint8 r, g, b, a;
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    Color(int r, int g, int b, int a = 255);
    Color toGrayscale();
    Color invert();
    SDL_Color toSDLColor() const;

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
}