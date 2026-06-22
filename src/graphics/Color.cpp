#include "graphics/Color.hpp"

namespace GameEngine{
Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}
Color::Color(int r, int g, int b, int a) : r(static_cast<Uint8>(r)), g(static_cast<Uint8>(g)), b(static_cast<Uint8>(b)), a(static_cast<Uint8>(a)) {}
Color Color::toGrayscale(){
    int gray = (static_cast<int>(r) + static_cast<int>(g) + static_cast<int>(b)) / 3;
    return Color(gray, gray, gray, a);
}
Color Color::invert(){
    return Color(255 - r, 255 - g, 255 - b, a);
}
SDL_Color Color::toSDLColor() const {
    return SDL_Color{r, g, b, a};
}
const Color Color::RED{255, 0, 0};
const Color Color::GREEN{0, 255, 0};
const Color Color::BLUE{0, 0, 255};
const Color Color::BLACK{0, 0, 0};
const Color Color::WHITE{255, 255, 255};
const Color Color::CYAN{0, 255, 255};
const Color Color::DARK_GRAY{64, 64, 64};
const Color Color::LIGHT_GRAY{192, 192, 192};
const Color Color::MAGENTA{255, 0, 255};
const Color Color::ORANGE{255, 165, 0};
const Color Color::PINK{255, 192, 203};
const Color Color::YELLOW{255, 255, 0};
}