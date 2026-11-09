#include "UniformStore.h"

void UniformStore::AddUniform(const std::string& name)
{
	if (!UniformExists(name))
	{
		uniformMap.insert({name, std::monostate()});
	}
}

bool UniformStore::UniformExists(const std::string& name)
{
	return (uniformMap.find(name) != uniformMap.end());
}
