#pragma once

#include <memory>

#include "Window/Window.h"
#include "Managers/Time/TimeManager.h"
#include "Managers/Time/TimeModule.h"
#include "Managers/Event/EventManager.h"
#include "Managers/Event/InputModule.h"
#include "Managers/Render/RenderManager.h"
#include "Scene/SceneManager/SceneManager.h"

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
	std::unique_ptr<SceneManager> sceneManager;
};
