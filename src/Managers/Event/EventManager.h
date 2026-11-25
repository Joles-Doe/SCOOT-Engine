#pragma once

#include <SDL.h>
#include <cstring>
#include <memory>

#include "InputModule.h"

enum class PollResponse
{
	QUIT,
	CONTINUE
};

class EventManager
{
public:
	EventManager();
	~EventManager();

	PollResponse PollEvents();

	std::shared_ptr<InputModule> GetInputModule();
private:
	std::shared_ptr<InputModule> inputModule;
};
