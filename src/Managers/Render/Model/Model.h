#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex
{
	glm::vec3 position{ 0.0f };
	glm::vec2 texCoord{ 0.0f };
	glm::vec3 normal{ 0.0f };
};

class Model
{
public:
	Model(const std::string& name);
	~Model();

	std::size_t GetVertexCount() const;
	std::size_t GetIndexCount() const;
	void Bind() const;

private:
	std::string modelName;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;

	void LoadModel(const std::string& path);
	void SetupMesh();
};
