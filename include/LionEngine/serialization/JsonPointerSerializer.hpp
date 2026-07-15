#pragma once
#include <nlohmann/json.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN
template <typename T>
struct adl_serializer<T*> {
    static void to_json(json& j, const T* ptr) {
        if (!ptr)
            j = nullptr;
        else
            j = *ptr;
    }

    static void from_json(const json& j, T*& ptr) {
        if (j.is_null()) {
            ptr = nullptr;
        } else {
            ptr = new T();
            j.get_to(*ptr);
        }
    }
};
NLOHMANN_JSON_NAMESPACE_END