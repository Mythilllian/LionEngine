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
    Entity(Entity* parent, const std::string& name = "Entity", const Transform& localTransform = Transform(), bool isGlobalTransform = false, bool active = true);
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
    T* copyComponent(T *component)
    {
        static_assert(std::is_base_of<Component, T>::value, "Tried to add a non-Component type to Components.");
        T* clonedComponent = component->clone(this);
        components.push_back(clonedComponent);
        return clonedComponent;
    }
    template <typename T>
    T* getComponent() const
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
    T* getComponentInChildren() const
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
    std::vector<T*> getComponentsInChildren() const
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
    T* getComponentInDescendants() const
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
    std::vector<T*> getComponentsInDescendants() const
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
    bool enabled = true;
private:
    std::vector<Component*> components;
    Entity* parent;
    std::vector<Entity*> children;
};
}