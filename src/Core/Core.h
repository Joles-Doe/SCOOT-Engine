#pragma once

#include <memory>

#include "Window/Window.h"
#include "Managers/Time/TimeManager.h"
#include "Managers/Event/EventManager.h"

class Core : public std::enable_shared_from_this<Core>
{
public:
	Core();
	~Core();

	void Update();
	bool QuitProgram();
private:
	bool quit{ false };

	std::unique_ptr<Window> sdlWindow;
	
	std::unique_ptr<TimeManager> timeManager;
	std::unique_ptr<EventManager> eventManager;
};