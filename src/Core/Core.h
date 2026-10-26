#pragma once

#include <memory>

#include "Window/Window.h"
#include "Managers/Time/TimeManager.h"

class Core : public std::enable_shared_from_this<Core>
{
public:
	Core();
	~Core();

	void Update();
private:
	std::unique_ptr<Window> sdlWindow;
	
	std::unique_ptr<TimeManager> timeManager;
};