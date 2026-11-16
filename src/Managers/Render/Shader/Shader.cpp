#include "Shader.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		throw std::runtime_error("Shader File read error");
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShaderID);

	GLint success = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << vertexShaderCode << std::endl;
		throw std::runtime_error("Vertex Shader compile error");
	}

	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Fragment Shader compile error");
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShaderID);
	glAttachShader(id, fragmentShaderID);

	glBindAttribLocation(id, 0, "aPosition");
	glBindAttribLocation(id, 1, "aPixelColor");
	glBindAttribLocation(id, 2, "aNormal");

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Shader link error");
	}

	glDetachShader(id, vertexShaderID);
	glDetachShader(id, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

Shader::~Shader()
{
	if (id)
	{
		glDeleteProgram(id);
	}
}

GLuint Shader::ID()
{
	return id;
}

std::vector<std::string>& Shader::GetUniformList()
{
	return uniforms;
}

/*
TO-DO
Initialize shader

Identify Attributes
Identify Uniforms
(Could store this in a separate file and read from it?)

That way, when shader is called to draw
-> Check what uniforms shader uses
-> Use a set function to iterate through each uniform (communicate with uniform store)

*/