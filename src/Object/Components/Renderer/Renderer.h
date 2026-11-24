#pragma once

#include <string>

struct Renderer
{
	Renderer(std::string modelKey, std::string textureKey) : modelName(modelKey), textureName(textureKey) {}

	std::string modelName;
	std::string textureName;
};