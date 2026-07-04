#pragma once

namespace GameEngine {
class Game {
public:
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void shutdown() = 0;
};
}