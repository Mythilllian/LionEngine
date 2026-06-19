namespace GameEngine {
class Color{
public:
    // Color values range from 0-255 (inclusive)
    int r, g, b;
    Color(int r, int g, int b);
    Color toGrayscale();
    Color invert();

    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color BLACK;
    static const Color WHITE;
    static const Color CYAN;
    static const Color DARK_GRAY;
    static const Color GREEN;
    static const Color LIGHT_GRAY;
    static const Color MAGENTA;
    static const Color ORANGE;
    static const Color PINK;
    static const Color YELLOW;
};
}