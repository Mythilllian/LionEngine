#pragma once
#include <vector>
#include <string>
#include "components/Component.hpp"
#include "components/Transform.hpp"
#include "math/Vector2.hpp"

namespace GameEngine {
class Component;
class Entity {
public:
    Entity(Entity* parent, const std::string& name = "Entity", const Transform& localTransform = Transform());
    ~Entity() = default;
    void init();
    void start();
    void update(float deltaTime);
    void shutdown();
    template <typename T>
    T* addComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "Tried to add a non-Component type to Components.");
        T* component = new T(this);
        components.push_back(component);
        return component;
    }
    template <typename T>
    T* getComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "Tried to get a non-Component type from Components.");
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
    T* getComponentInChildren()
    {
        static_assert(std::is_base_of<Component, T>::value, "Tried to get a non-Component type from Components.");
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
    std::vector<T*> getComponentsInChildren()
    {
        static_assert(std::is_base_of<Component, T>::value, "Tried to get a non-Component type from Components.");
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
    T* getComponentInDescendants()
    {
        static_assert(std::is_base_of<Component, T>::value, "Tried to get a non-Component type from Components.");
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
    std::vector<T*> getComponentsInDescendants()
    {
        static_assert(std::is_base_of<Component, T>::value, "Tried to get a non-Component type from Components.");
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
        static_assert(std::is_base_of<Component, T>::value, "Tried to remove a non-Component type from Components.");
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
    Entity* getParent();
    void setParent(Entity* parent);
    std::vector<Entity*> getChildren() const;
    void addChild(Entity* child);
    void removeChild(Entity* child);
    Entity* getDescendantByName(const std::string& name);
    Entity* getChildByName(const std::string& name);
    std::string name;
    bool active = true;
    Transform localTransform;
    Transform globalTransform() const;
    void updateGlobalTransform(Transform transform);
    void updateGlobalTransform(Vector2 position = Vector2{0, 0}, Vector2 scale = Vector2{1, 1}, float rotation = 0);
private:
    std::vector<Component*> components;
    Entity* parent;
    std::vector<Entity*> children;
};
}