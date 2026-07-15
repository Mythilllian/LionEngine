#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace LionEngine {
class Asset {
public:
    std::string path;
    Asset(const std::string& path);
    Asset();
    virtual ~Asset() = default;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Asset, path)
}