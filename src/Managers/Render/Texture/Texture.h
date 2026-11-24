#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>

class Texture
{
public:
	Texture(const std::string& name);
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;

	void Bind() const;

private:
	void Load(const std::string& path);
	void Setup();

	GLuint id{};

	std::string textureName;
	std::vector<unsigned char> data;
	glm::ivec2 size{ 0 };
};
