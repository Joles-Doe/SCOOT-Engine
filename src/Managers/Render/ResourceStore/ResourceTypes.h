#include <glm/glm.hpp>

#include "Managers/Render/ResourceStore/ResourceStore.h"

using UniformStore = ResourceStore<
	glm::mat4,
	glm::vec4,
	glm::vec3,
	glm::vec2,
	float
>;

using ShaderStore = ResourceStore<
	//ShaderProgram Object
>;