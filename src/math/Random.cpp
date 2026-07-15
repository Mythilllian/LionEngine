#include "LionEngine/math/Random.hpp"

namespace LionEngine {
std::mt19937 Random::generator;
void Random::seed(unsigned int seed) {
    generator.seed(seed);
}
int Random::range(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max - 1);
    return distribution(generator);
}
float Random::range(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}
}