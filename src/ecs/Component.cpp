#include "LionEngine/ecs/Component.hpp"

namespace LionEngine {
Component::Component(Entity* parent) : parent(parent) {}
void Component::init() {}
void Component::start() {}
void Component::update(float deltaTime) {}
void Component::shutdown() {}
void Component::onEvent(const std::string& eventName, void* eventData) {}
json Component::serialize() const {
    json j;
    j["type"] = ComponentRegistry::getComponentName(this);
    j["active"] = active;
    for (const auto& field : fields) {
        field.save(j["fields"]);
    }
    return j;
}
void Component::deserialize(const json& j) {
    active = j.value("active", true);
    for (const auto& field : fields) {
        field.load(j["fields"]);
    }
}
Component* Component::clone(Entity* newParent) {
    Component* newComponent = ComponentRegistry::createComponent(ComponentRegistry::getComponentName(this), newParent);
    if (newComponent) {
        for (const auto& field : fields) {
            field.save(newComponent->serialize()["fields"]);
        }
    }
    return newComponent;
}
Entity* Component::getParent() const {
    return parent;
}
}