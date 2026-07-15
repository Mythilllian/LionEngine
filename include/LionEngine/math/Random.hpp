#pragma once
#include <random>

namespace LionEngine {
class Random {
public:
    static void seed(unsigned int seed);
    static int range(int min, int max); // Returns a random integer in the range [min, max)
    static float range(float min, float max); // Returns a random float in the range [min, max)
private:
    static std::mt19937 generator;
};
}