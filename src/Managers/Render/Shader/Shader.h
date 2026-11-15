#pragma once

#include <string>
#include <GL/glew.h>
#include <fstream>

class Shader
{
public:
	Shader(std::string vertexPath, std::string fragmentPath);

private:
	GLuint id;
};