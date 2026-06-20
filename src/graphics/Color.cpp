#include "graphics/Color.hpp"

namespace GameEngine{
Color::Color(int r, int g, int b) : r(r), g(g), b(b) {}
Color Color::toGrayscale(){
    int gray = (r + g + b) / 3;
    return Color(gray, gray, gray);
}
Color Color::invert(){
    return Color(255 - r, 255 - g, 255 - b);
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