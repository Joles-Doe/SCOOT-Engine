#include "Texture.h"

Texture::Texture(const std::string& name) : textureName(name)
{
	const std::filesystem::path textureDirectory = std::filesystem::path("assets/textures") / name;
	const char* extensions[] = {
		".png", ".jpg", ".jpeg"
	};

	std::filesystem::path texturePath;
	for (const char* extension : extensions)
	{
		const auto candidate = textureDirectory / (name + extension);
		if (std::filesystem::exists(candidate))
		{
			texturePath = candidate;
			break;
		}
	}

	if (texturePath.empty())
	{
		texturePath = textureDirectory / (name + ".png");
	}

	Load(texturePath.string());
	Setup();
}

Texture::~Texture()
{
	if (id)
	{
		glDeleteTextures(1, &id);
	}
}

Texture::Texture(Texture&& other) noexcept
	: id(std::exchange(other.id, 0)),
	  textureName(std::move(other.textureName)),
	  data(std::move(other.data)),
	  size(other.size)
{
	other.size = glm::ivec2(0);
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	if (this != &other)
	{
		if (id)
			glDeleteTextures(1, &id);

		id = std::exchange(other.id, 0);
		textureName = std::move(other.textureName);
		data = std::move(other.data);
		size = other.size;
		other.size = glm::ivec2(0);
	}

	return *this;
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Load(const std::string& path)
{
	unsigned char* textureData = stbi_load(path.c_str(), &size.x, &size.y, NULL, 4);

	if (!textureData)
	{
		throw std::runtime_error("Failed to Load Texture");
	}

	for (int x = 0; x < (size.x * size.y * 4); x++)
	{
		data.push_back(textureData[x]);
	}
	free(textureData);
}

void Texture::Setup()
{
	glGenTextures(1, &id);
	if (!id)
	{
		throw std::runtime_error("Failed to Initialize Texture");
	}

	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
