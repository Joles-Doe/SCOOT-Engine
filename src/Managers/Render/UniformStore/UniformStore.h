#pragma once

#include <string>
#include <variant>
#include <glm/glm.hpp>

class UniformStore
{
public:
	void AddUniform(const std::string& name);

	template <typename T>
	void SetUniform(const std::string& name, const T& value);

	template <typename T>
	T GetUniform(const std::string& name);
private:
	bool UniformExists(const std::string& name);
	
	using uniformValues = std::variant<glm::mat4, glm::vec4, glm::vec3, glm::vec2, float, std::monostate>;
	std::unordered_map<std::string, uniformValues> uniformMap;
};

template <typename T>
void UniformStore::SetUniform(const std::string& name, const T& value)
{
	if (UniformExists(name))
	{
		uniformMap[name] = value;
	}
}

template <typename T>
T UniformStore::GetUniform(const std::string& name)
{
	if (UniformExists(name))
	{
		return std::get<T>(uniformMap[name]);
	}
	return T{};
}