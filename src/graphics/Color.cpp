#include "LionEngine/graphics/Color.hpp"

namespace LionEngine{
Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}
Color Color::toGrayscale(){
    Uint8 gray = static_cast<Uint8>((static_cast<int>(r) + static_cast<int>(g) + static_cast<int>(b)) / 3);
    return Color(gray, gray, gray, a);
}
Color Color::invert(){
    return Color(255 - r, 255 - g, 255 - b, a);
}
SDL_Color Color::toSDLColor() const {
    return SDL_Color{r, g, b, a};
}
Color Color::random() {
    Uint8 r = static_cast<Uint8>(Random::range(0, 256));
    Uint8 g = static_cast<Uint8>(Random::range(0, 256));
    Uint8 b = static_cast<Uint8>(Random::range(0, 256));
    return Color(r, g, b, 255);
}
Color Color::operator*(float scalar) const {
    return Color(static_cast<Uint8>(r * scalar), static_cast<Uint8>(g * scalar), static_cast<Uint8>(b * scalar), a);
}
Color Color::operator*(const Color other) const {
    return Color(static_cast<Uint8>(r * other.r / 255), static_cast<Uint8>(g * other.g / 255), static_cast<Uint8>(b * other.b / 255), a);
}
Color Color::operator*(float scalar) {
    r = static_cast<Uint8>(r * scalar);
    g = static_cast<Uint8>(g * scalar);
    b = static_cast<Uint8>(b * scalar);
    return *this;
}
Color Color::operator*(const Color other) {
    r = static_cast<Uint8>(r * other.r / 255);
    g = static_cast<Uint8>(g * other.g / 255);
    b = static_cast<Uint8>(b * other.b / 255);
    return *this;
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
void from_json(const nlohmann::json& j, Color& u) {
    j.at("r").get_to(u.r);
    j.at("g").get_to(u.g);
    j.at("b").get_to(u.b);
    if(j.contains("a")) {
        j.at("a").get_to(u.a);
    }
}
void to_json(nlohmann::json& j, const Color& u) {
    j = nlohmann::json{{"r", u.r}, {"g", u.g}, {"b", u.b}, {"a", u.a}};
}
}