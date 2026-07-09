#pragma once
#include <unordered_map>
#include <string>
#include <typeindex>

namespace GameEngine {
class Entity;
class Component;
class ComponentRegistry {
public:
    static void registerComponent(const std::string& typeName, std::type_index typeIndex, Component* (*createFunc)(Entity*));
    static Component* createComponent(const std::string& typeName, Entity* parent);
    static std::string getComponentName(const Component* component);
    static bool isComponentRegistered(const std::string& typeName);
private:
    static std::unordered_map<std::string, Component* (*)(Entity*)>& creatorRegistry();
    static std::unordered_map<std::type_index, std::string>& nameRegistry();
};
}