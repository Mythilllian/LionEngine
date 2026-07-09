#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include "serialization/JsonPointerSerializer.hpp"
#include "utils/Logger.hpp"
#include <typeindex>
#include "ecs/ComponentRegistry.hpp"

#define SERIALIZEFIELD(field) expose(#field, field)
#define REGISTERCOMPONENT(className) \
    namespace { \
        struct className##Registrar { \
            className##Registrar() { \
                ComponentRegistry::registerComponent(#className, std::type_index(typeid(className)), [](Entity* parent) -> Component* { return new className(parent); }); \
            } \
        }; \
        static className##Registrar global_##className##Registrar; \
    }
    
using json = nlohmann::json;

namespace GameEngine {
class Entity;
class Component {
public:
    Component(Entity* parent);
    virtual ~Component() = default;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void shutdown() = 0;
    Component* clone(Entity* newParent);
    bool active = true;
    json serialize() const;
    void deserialize(const json&);
    Entity* getParent() const;
protected:
    Entity* parent;
    struct Field
    {
        std::string name;
        std::function<void(json&)> save;
        std::function<void(const json&)> load;
    };
    std::vector<Field> fields;
    template<typename T>
    void expose(const char* name, T& value) {
        fields.push_back({
            name,
            [&value, name](json& j) {
                j[name] = value;
            },
            [&value, name](const json& j) {
                if (j.contains(name)) {
                    value = j[name].get<T>();
                }
            }
        });
    }
};
// void from_json(const json& j, Component& u);
// void to_json(json& j, const Component& u);
}