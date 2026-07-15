#include "LionEngine/assets/Asset.hpp"

namespace LionEngine {
Asset::Asset(const std::string& path) : path(path) {}
Asset::Asset() : path("") {}
}