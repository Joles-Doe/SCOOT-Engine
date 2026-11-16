#pragma once

#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>

template <typename... Types>
class ResourceStore
{
public:
    using ResourceVariant = std::variant<Types...>;

    void Set(const std::string& name, ResourceVariant resource)
    {
        resources.insert_or_assign(name, std::move(resource));
    }

    template <typename T>
    T* Get(const std::string& name)
    {
        auto it = resources.find(name);

        if (it != resources.end())
            return std::get_if<T>(&it->second);

        return nullptr;
    }

    ResourceVariant* Get(const std::string& name)
    {
        auto it = resources.find(name);

        if (it != resources.end())
            return &it->second;

        return nullptr;
    }

private:
    std::unordered_map<std::string, ResourceVariant> resources;
};
