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
	glBindAttribLocation(id, 3, "aTexCoord");

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Shader link error");
	}

	GLint uniformCount = 0;
	GLint maxNameLength = 0;
	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &uniformCount);
	glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

	std::vector<GLchar> nameBuffer(maxNameLength);

	for (GLint i = 0; i < uniformCount; ++i)
	{
		GLsizei nameLength = 0;
		GLint arraySize = 0;
		GLenum type = 0;

		glGetActiveUniform(
			id,
			static_cast<GLuint>(i),
			maxNameLength,
			&nameLength,
			&arraySize,
			&type,
			nameBuffer.data()
		);

		uniforms.emplace_back(nameBuffer.data(), nameLength);
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

Shader::Shader(Shader&& other) noexcept
	: id(std::exchange(other.id, 0)),
	  uniforms(std::move(other.uniforms))
{
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		if (id)
		{
			glDeleteProgram(id);
		}

		id = std::exchange(other.id, 0);
		uniforms = std::move(other.uniforms);
	}

	return *this;
}

GLuint Shader::ID()
{
	return id;
}

void Shader::SetUniform(const std::string& name, const glm::mat4& value)
{
	GLint location = glGetUniformLocation(id, name.c_str());
	if (location == -1) return;

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, const glm::vec4& value)
{
	GLint location = glGetUniformLocation(id, name.c_str());
	if (location == -1) return;

	glUniform4fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(id, name.c_str());
	if (location == -1) return;

	glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, const glm::vec2& value)
{
	GLint location = glGetUniformLocation(id, name.c_str());
	if (location == -1) return;

	glUniform2fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(id, name.c_str());
	if (location == -1) return;

	glUniform1f(location, value);
}

std::vector<std::string>& Shader::GetUniformList()
{
	return uniforms;
}
