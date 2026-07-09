#pragma once
#include <vector>
#include <string>
#include "ecs/Component.hpp"
#include "ecs/Transform.hpp"
#include "math/Vector2.hpp"
#include "utils/Logger.hpp"

namespace GameEngine {
class Component;
class Entity {
public:
    Entity(Entity* parent = nullptr, const std::string& name = "Entity", const Transform& localTransform = Transform(), bool isGlobalTransform = false, bool active = true);
    ~Entity() = default;
    void init();
    void start();
    void update(float deltaTime);
    void shutdown();
    template <typename T>
    T* addComponent()
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to add a non-Component type to %s.", name.c_str());
            return nullptr;
        }
        T* component = new T(this);
        components.push_back(component);
        return component;
    }
    Component* addComponent(Component* component)
    {
        if(component->getParent() != this) {
            Logger::logError("Tried to add a Component that does not belong to this Entity.");
            return nullptr;
        }
        components.push_back(component);
        return component;
    }
    template <typename T>
    T* copyComponent(T *component)
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to copy a non-Component type to %s.", name.c_str());
            return nullptr;
        }
        T* clonedComponent = component->clone(this);
        components.push_back(clonedComponent);
        return clonedComponent;
    }
    template <typename T>
    T* getComponent() const
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to get a non-Component type from %s.", name.c_str());
            return nullptr;
        }
        for (auto& component : components)
        {
            if (T* castedComponent = dynamic_cast<T*>(component))
            {
                return castedComponent;
            }
        }
        return nullptr;
    }
    template <typename T>
    T* getComponentInChildren() const
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to get a non-Component type from %s.", name.c_str());
            return nullptr;
        }
        for (auto& child : children)
        {
            if (T* component = child->getComponent<T>())
            {
                return component;
            }
        }
        return nullptr;
    }
    template <typename T>
    std::vector<T*> getComponentsInChildren() const
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to get a non-Component type from %s.", name.c_str());
            return std::vector<T*>();
        }
        std::vector<T*> components;
        for (auto& child : children)
        {
            if (T* component = child->getComponent<T>())
            {
                components.push_back(component);
            }
        }
        return components;
    }
    template <typename T>
    T* getComponentInDescendants() const
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to get a non-Component type from %s.", name.c_str());
            return nullptr;
        }
        for (auto& child : children)
        {
            if (T* component = child->getComponent<T>())
            {
                return component;
            }
            if (T* component = child->getComponentInDescendants<T>())
            {
                return component;
            }
        }
        return nullptr;
    }
    template <typename T>
    std::vector<T*> getComponentsInDescendants() const
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to get a non-Component type from %s.", name.c_str());
            return std::vector<T*>();
        }
        std::vector<T*> components;
        for (auto& child : children)
        {
            if (T* component = child->getComponent<T>())
            {
                components.push_back(component);
            }
            auto childComponents = child->getComponentsInDescendants<T>();
            components.insert(components.end(), childComponents.begin(), childComponents.end());
        }
        return components;
    }
    template <typename T>
    bool removeComponent()
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to remove a non-Component type from %s.", name.c_str());
            return false;
        }
        for (auto it = components.begin(); it != components.end(); ++it)
        {
            if (T* castedComponent = dynamic_cast<T*>(*it))
            {
                delete castedComponent;
                components.erase(it);
                return true;
            }
        }
        return false;
    }
    std::vector<Component*> getComponents() const;
    Entity* getParent() const;
    void setParent(Entity* parent, bool keepGlobalTransform = true);
    std::vector<Entity*> getChildren() const;
    std::vector<Entity*> getDescendants() const;
    void addChild(Entity* child, bool keepGlobalTransform = true);
    void removeChild(Entity* child);
    Entity* getDescendantByName(const std::string& name) const;
    Entity* getChildByName(const std::string& name) const;
    std::string name;
    bool active = true;
    Transform localTransform;
    Transform globalTransform() const;
    void updateGlobalTransform(Transform transform);
    void updateGlobalTransform(Vector2 position = Vector2{0, 0}, Vector2 scale = Vector2{1, 1}, float rotation = 0);
    Entity* clone(bool keepGlobalTransform = true) const;
private:
    std::vector<Component*> components;
    Entity* parent;
    std::vector<Entity*> children;
};
void from_json(const nlohmann::json& j, Entity& u);
void to_json(nlohmann::json& j, const Entity& u);
}