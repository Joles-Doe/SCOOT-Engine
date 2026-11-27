#pragma once

#include <string>

struct Renderer
{
	Renderer(std::string modelKey, std::string textureKey) : modelName(modelKey), textureName(textureKey) {}

	std::string modelName;
	std::string textureName;
	glm::vec3 baseColor{ 1.0f }; // Tint (Default is 1,1,1 - Unchanged tint)
	glm::vec3 specularColor{ 1.0f }; // Tint of the specular highlight (Default is 1,1,1 - Unchanged tint) 
	float specularStrength{ 0.25f }; // Strength of the specular highlight
	float shininess{ 32.0f }; // How tightly focused the specular highlight is
};