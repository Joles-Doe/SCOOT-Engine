#include <glm/glm.hpp>

#include "Managers/Render/ResourceStore/ResourceStore.h"

#include "Managers/Render/Shader/Shader.h"
#include "Managers/Render/Model/Model.h"
#include "Managers/Render/Texture/Texture.h"

using UniformStore = ResourceStore<
	glm::mat4,
	glm::vec4,
	glm::vec3,
	glm::vec2,
	float,
	int,
	std::monostate
>;

using ShaderStore = ResourceStore<
	Shader,
	std::monostate
>;

using ModelStore = ResourceStore<
	Model,
	std::monostate
>;

using TextureStore = ResourceStore<
	Texture,
	std::monostate
>;