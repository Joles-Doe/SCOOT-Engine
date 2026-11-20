#pragma once

#include <glm/glm.hpp>

class Transform
{
public:
	Transform() : position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f))
	{}

	void Move(glm::vec3 movement) noexcept { position += movement; }
	void Rotate(glm::vec3 rot) noexcept { rotation += rot; }

	void Position(glm::vec3 pos) noexcept { position = pos; }
	glm::vec3 Position() const noexcept { return position; }

	void Rotation(glm::vec3 rot) noexcept { rotation = rot; }
	glm::vec3 Rotation() { return rotation; }

	void Scale(glm::vec3 scale) noexcept { scale = scale; }
	glm::vec3 Scale() const noexcept { return scale; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};