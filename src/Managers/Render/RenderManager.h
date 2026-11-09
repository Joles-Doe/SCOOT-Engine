#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Window/Window.h"
#include "UniformStore/UniformStore.h"

class RenderManager
{
public:
	RenderManager(std::weak_ptr<Window> window);
	~RenderManager();

	void DrawObjects();
private:
	std::weak_ptr<Window> engineWindow;
	std::pair<int, int> windowSize;

	std::shared_ptr<UniformStore> uniformStore;
};