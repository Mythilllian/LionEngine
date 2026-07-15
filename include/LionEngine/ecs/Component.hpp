#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include "LionEngine/serialization/JsonPointerSerializer.hpp"
#include "LionEngine/utils/Logger.hpp"
#include <typeindex>
#include "LionEngine/ecs/ComponentRegistry.hpp"

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

namespace LionEngine {
class Entity;
class Component {
public:
    Component(Entity* parent);
    virtual ~Component() = default;
    virtual void init();
    virtual void start();
    virtual void update(float deltaTime);
    virtual void shutdown();
    virtual void onEvent(const std::string& eventName, void* eventData);
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
}