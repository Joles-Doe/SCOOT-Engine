#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <filesystem>

#include "Window/Window.h"
#include "Managers/Render/ResourceStore/ResourceTypes.h"
#include "Managers/Render/Shader/Shader.h"

class RenderManager
{
public:
	RenderManager(std::weak_ptr<Window> window);
	~RenderManager();

	void DrawObjects();
private:
	std::weak_ptr<Window> engineWindow;
	std::pair<int, int> windowSize;

	std::shared_ptr<ShaderStore> CompileShaders();

	std::shared_ptr<UniformStore> uniformStore;
	std::shared_ptr<ShaderStore> shaderStore;
};