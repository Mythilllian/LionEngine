#pragma once

namespace GameEngine {
class Component {
public:
    virtual ~Component() = default;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void run(float deltaTime) = 0;
    virtual void shutdown() = 0;
};
}