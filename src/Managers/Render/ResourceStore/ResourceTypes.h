#include <glm/glm.hpp>

#include "Managers/Render/ResourceStore/ResourceStore.h"
#include "Managers/Render/Shader/Shader.h"

using UniformStore = ResourceStore<
	glm::mat4,
	glm::vec4,
	glm::vec3,
	glm::vec2,
	float,
	std::monostate
>;

using ShaderStore = ResourceStore<
	Shader,
	std::monostate
>;