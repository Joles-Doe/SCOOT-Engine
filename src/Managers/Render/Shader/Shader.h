#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader(); // Necessary for std::variant
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	GLuint ID();
	std::vector<std::string>& GetUniformList();

	template <typename T>
	void SetUniform(const std::string& name, const T& value);
private:
	GLuint id;

	std::vector<std::string> uniforms;
};