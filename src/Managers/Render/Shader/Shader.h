#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <utility>

class Shader
{
public:
	Shader() = default;
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	GLuint ID();
	std::vector<std::string>& GetUniformList();

	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(const std::string& name, const glm::vec4& value);
	void SetUniform(const std::string& name, const glm::vec3& value);
	void SetUniform(const std::string& name, const glm::vec2& value);
	void SetUniform(const std::string& name, float value);
private:
	GLuint id{};

	std::vector<std::string> uniforms;
};
