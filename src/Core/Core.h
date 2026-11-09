#pragma once

#include <memory>

#include "Window/Window.h"
#include "Managers/Time/TimeManager.h"
#include "Managers/Event/EventManager.h"
#include "Managers/Render/RenderManager.h"

class Core
{
public:
	Core();
	~Core();

	void Update();
	bool QuitProgram();
private:
	bool quit{ false };

	std::shared_ptr<Window> sdlWindow;
	
	std::unique_ptr<TimeManager> timeManager;
	std::unique_ptr<EventManager> eventManager;
	std::unique_ptr<RenderManager> renderManager;
};