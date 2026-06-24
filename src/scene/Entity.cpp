#include "scene/Entity.hpp"
#include <algorithm>

namespace GameEngine
{
Entity::Entity(Entity* parent, const std::string& name, const Transform& localTransform) : parent(parent), localTransform(localTransform)
{
    if(parent != nullptr){
        parent->addChild(this);
    }
    if(parent != nullptr && parent->getChildByName(name) != nullptr){
        int i = 1;
        while (parent->getChildByName(name + std::to_string(i)) != nullptr) {
            i++;
        }
        this->name = name + std::to_string(i);
    }
    else{
        this->name = name;
    }
}
void Entity::init()
{
    for (auto& component : components)
    {
        component->init();
    }
    for (auto& child : children)
    {
        child->init();
    }
}
void Entity::start()
{
    for (auto& component : components)
    {
        component->start();
    }
    for (auto& child : children)
    {
        child->start();
    }
}
void Entity::update(float deltaTime)
{
    for (auto& component : components)
    {
        if (component->active)
        {
            component->update(deltaTime);
        }
    }
    for (auto& child : children)
    {
        if (child->active)
        {
            child->update(deltaTime);
        }
    }
}
void Entity::shutdown()
{
    for (auto& component : components)
    {
        component->shutdown();
    }
    for (auto& child : children)
    {
        child->shutdown();
    }
}
std::vector<Component*> Entity::getComponents() const
{
    return components;
}
Entity* Entity::getParent()
{
    return parent;
}
void Entity::setParent(Entity* parent)
{
    this->parent->removeChild(this);
    this->parent = parent;
    this->parent->addChild(this);
}
std::vector<Entity*> Entity::getChildren() const
{
    return children;
}
void Entity::addChild(Entity* child)
{
    children.push_back(child);
}
void Entity::removeChild(Entity* child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}
Entity* Entity::getDescendantByName(const std::string& name)
{
    for (auto& child : children)
    {
        if (child->name == name)
        {
            return child;
        }
        Entity* descendant = child->getDescendantByName(name);
        if (descendant != nullptr)
        {
            return descendant;
        }
    }
    return nullptr;
}
Entity* Entity::getChildByName(const std::string& name)
{
    for (auto& child : children)
    {
        if (child->name == name)
        {
            return child;
        }
    }
    return nullptr;
}
Transform Entity::globalTransform() const
{
    if (parent == nullptr)
    {
        return localTransform;
    }
    return parent->globalTransform() * localTransform;
}
void Entity::updateGlobalTransform(Transform transform)
{
    localTransform = transform / globalTransform();
}
void Entity::updateGlobalTransform(Vector2 position, Vector2 scale, float rotation)
{
    updateGlobalTransform(Transform(position, scale, rotation));
}
}