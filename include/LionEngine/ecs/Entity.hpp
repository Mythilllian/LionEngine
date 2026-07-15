#pragma once
#include <vector>
#include <string>
#include "LionEngine/ecs/Component.hpp"
#include "LionEngine/ecs/Transform.hpp"
#include "LionEngine/math/Vector2.hpp"
#include "LionEngine/utils/Logger.hpp"

namespace LionEngine {
class Component;
class Entity {
public:
    Entity(Entity* parent = nullptr, const std::string& name = "Entity", const Transform& localTransform = Transform(), bool isGlobalTransform = false, bool active = true);
    ~Entity() = default;
    void init();
    void start();
    void update(float deltaTime);
    void shutdown();
    void callEvent(const std::string& eventName, bool recursive = false, void* eventData = nullptr);
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
    template <typename T>
    int getComponentIndex() const
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to get a non-Component type from %s.", name.c_str());
            return -1;
        }
        for (size_t i = 0; i < components.size(); ++i)
        {
            if (T* castedComponent = dynamic_cast<T*>(components[i]))
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }
    template <typename T, typename U>
    void swapComponentIndices()
    {
        if(!std::is_base_of<Component, T>::value || !std::is_base_of<Component, U>::value) {
            Logger::logError("Tried to swap non-Component types in %s.", name.c_str());
            return;
        }
        int indexT = getComponentIndex<T>();
        int indexU = getComponentIndex<U>();
        if (indexT != -1 && indexU != -1)
        {
            std::swap(components[indexT], components[indexU]);
        }
    }
    template <typename T>
    void setComponentIndex(int newIndex)
    {
        if(!std::is_base_of<Component, T>::value) {
            Logger::logError("Tried to set index of a non-Component type in %s.", name.c_str());
            return;
        }
        int currentIndex = getComponentIndex<T>();
        if (currentIndex != -1 && newIndex >= 0 && newIndex < static_cast<int>(components.size()))
        {
            Component* component = components[currentIndex];
            components.erase(components.begin() + currentIndex);
            components.insert(components.begin() + newIndex, component);
        }
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
    int getChildIndex(Entity* child) const;
    std::string name;
    bool active = true;
    bool centerTransform = true;
    Transform localTransform;
    Transform globalTransform() const;
    Transform globalTransform(bool centeredTransform) const;
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