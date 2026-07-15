#pragma once
#include <cmath>

namespace LionEngine {
class Round {
public:
    static float toNearest(float value, float nearest) {
        if (nearest == 0) {
            return value;
        }
        return std::round(value / nearest) * nearest;
    }
    static int toPlace(float value, int place) {
        float factor = std::pow(10.0f, place);
        return static_cast<int>(std::round(value * factor) / factor);
    }
};
}