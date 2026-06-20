#pragma once

#include <string>

namespace GameEngine {
class Asset {
public:
    const std::string& path;
    Asset(const std::string& path);
    virtual ~Asset() = default;
};
}