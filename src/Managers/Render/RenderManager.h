#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cstddef>
#include <filesystem>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Window/Window.h"
#include "Managers/Render/ResourceStore/ResourceTypes.h"
#include "Managers/Render/Shader/Shader.h"

#include "Object/Object.h"
#include "Object/Components/Base/Component.h"
#include "Object/Components/Transform/Transform.h"
#include "Object/Components/Renderer/Renderer.h"
#include "Object/Components/Light/Light.h"

struct LightData
{
	Light light;
	Transform transform;
};

class RenderManager
{
public:
	RenderManager(std::weak_ptr<Window> window);
	~RenderManager();

	void DrawObjects(const std::vector<std::shared_ptr<Object>>& objects);
private:
	std::weak_ptr<Window> engineWindow;
	std::pair<int, int> windowSize;

	std::shared_ptr<ShaderStore> CompileShaders();

	std::vector<const LightData*> GetLightsForObject(const std::vector<LightData>& lights, const glm::vec3& objectPosition) const;

	std::shared_ptr<UniformStore> uniformStore;
	std::shared_ptr<ShaderStore> shaderStore;
	std::shared_ptr<ModelStore> modelStore;
	std::shared_ptr<TextureStore> textureStore;

	static const std::size_t MaxLightsPerObject{ 16 };
};
