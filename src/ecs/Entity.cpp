#include "ecs/Entity.hpp"
#include <algorithm>
#include "ecs/ComponentRegistry.hpp"

namespace GameEngine
{
Entity::Entity(Entity* parent, const std::string& name, const Transform& transform, bool isGlobalTransform, bool active) : parent(parent), name(name), active(active)
{
    if(parent != nullptr){
        parent->addChild(this);
    }
    if(isGlobalTransform){
        updateGlobalTransform(transform);
    }
    else{
        localTransform = transform;
    }
    // if(parent != nullptr && parent->getChildByName(name) != nullptr){
    //     int i = 1;
    //     while (parent->getChildByName(name + std::to_string(i)) != nullptr) {
    //         i++;
    //     }
    //     this->name = name + std::to_string(i);
    // }
    // else{
    //     this->name = name;
    // }
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
Entity* Entity::getParent() const
{
    return parent;
}
void Entity::setParent(Entity* parent, bool keepGlobalTransform)
{
    if (keepGlobalTransform)
    {
        Transform globalTransform = this->globalTransform();
        if (this->parent != nullptr)
        {
            this->parent->removeChild(this);
        }
        this->parent = parent;
        this->parent->addChild(this);
        this->updateGlobalTransform(globalTransform);
    }
    else
    {
        if (this->parent != nullptr)
        {
            this->parent->removeChild(this);
        }
        this->parent = parent;
        this->parent->addChild(this);
    }
}
std::vector<Entity*> Entity::getChildren() const
{
    return children;
}
std::vector<Entity*> Entity::getDescendants() const
{
    std::vector<Entity*> descendants;
    for (auto& child : children)
    {
        descendants.push_back(child);
        auto childDescendants = child->getDescendants();
        descendants.insert(descendants.end(), childDescendants.begin(), childDescendants.end());
    }
    return descendants;
}
void Entity::addChild(Entity* child, bool keepGlobalTransform)
{
    if(keepGlobalTransform)
    {
        Transform globalTransform = child->globalTransform();
        child->parent = this;
        child->updateGlobalTransform(globalTransform);
    }
    else
    {
        child->parent = this;
    }
    children.push_back(child);
}
void Entity::removeChild(Entity* child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}
Entity* Entity::getDescendantByName(const std::string& name) const
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
Entity* Entity::getChildByName(const std::string& name) const
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
    localTransform = transform / parent->globalTransform();
}
void Entity::updateGlobalTransform(Vector2 position, Vector2 scale, float rotation)
{
    updateGlobalTransform(Transform(position, scale, rotation));
}
Entity* Entity::clone(bool keepGlobalTransform) const
{
    Entity* newEntity = new Entity(nullptr, name, keepGlobalTransform ? globalTransform() : localTransform);
    for (auto& component : components)
    {
        newEntity->copyComponent(component);
    }
    for (auto& child : children)
    {
        Entity* clonedChild = child->clone();
        newEntity->addChild(clonedChild);
    }
    return newEntity;
}
void from_json(const nlohmann::json& j, Entity& u)
{
    u.name = j.value("name", "");
    u.active = j.value("active", true);
    u.localTransform = j.value("localTransform", Transform());
    for (const auto& childJson : j["children"])
    {
        GameEngine::Entity* child = new GameEngine::Entity(&u);
        from_json(childJson, *child);
    }
    for (const auto& componentJson : j["components"])
    {
        std::string typeName = componentJson.value("type", "");
        if (GameEngine::ComponentRegistry::isComponentRegistered(typeName))
        {
            GameEngine::Component* component = GameEngine::ComponentRegistry::createComponent(typeName, &u);
            component->deserialize(componentJson);
            u.addComponent(component);
        }
        else
        {
            Logger::logWarning("Component type '%s' is not registered. Skipping deserialization.", typeName.c_str());
        }
    }
}
void to_json(nlohmann::json& j, const Entity& u)
{
    j["name"] = u.name;
    j["active"] = u.active;
    j["localTransform"] = u.localTransform;
    j["children"] = nlohmann::json::array();
    for (const auto& child : u.getChildren())
    {
        nlohmann::json childJson;
        to_json(childJson, *child);
        j["children"].push_back(childJson);
    }
    j["components"] = nlohmann::json::array();
    for (const auto& component : u.getComponents())
    {
        j["components"].push_back(component->serialize());
    }
}
}