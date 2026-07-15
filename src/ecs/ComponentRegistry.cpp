#include "LionEngine/ecs/ComponentRegistry.hpp"
#include "LionEngine/ecs/Entity.hpp"
#include "LionEngine/ecs/Component.hpp"

namespace LionEngine {
    void ComponentRegistry::registerComponent(const std::string& typeName, std::type_index typeIndex, Component* (*createFunc)(Entity*)) {
        creatorRegistry()[typeName] = createFunc;
        nameRegistry()[typeIndex] = typeName;
    }
    Component* ComponentRegistry::createComponent(const std::string& typeName, Entity* parent)
    {
        return creatorRegistry()[typeName](parent);
    }
    std::string ComponentRegistry::getComponentName(const Component* component) {
        return nameRegistry()[std::type_index(typeid(*component))];
    }
    bool ComponentRegistry::isComponentRegistered(const std::string& typeName) {
        return creatorRegistry()[typeName] != nullptr;
    }
    std::unordered_map<std::string, Component* (*)(Entity*)>& ComponentRegistry::creatorRegistry() {
        static std::unordered_map<std::string, Component* (*)(Entity*)> instance;
        return instance;
    }
    std::unordered_map<std::type_index, std::string>& ComponentRegistry::nameRegistry() {
        static std::unordered_map<std::type_index, std::string> instance;
        return instance;
    }
}