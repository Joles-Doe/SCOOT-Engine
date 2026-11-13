#pragma once

#include <variant>

template <typename... Types>
class ResourceStore
{
public:
    using ResourceVariant = std::variant<Types...>;

    void Set(const std::string& name, const ResourceVariant& resource)
    {
        resources[name] = resource;
    }

    template <typename T>
    T* Get(const std::string& name)
    {
        auto it = resources.find(name);

        if (it != resources.end())
            return std::get_if<T>(&it->second);

        return nullptr;
    }

private:
    std::unordered_map<std::string, ResourceVariant> resources;
};