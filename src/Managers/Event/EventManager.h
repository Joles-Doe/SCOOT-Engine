#pragma once

#include <SDL.h>
#include <cstring>
#include <memory>

#include "Input.h"

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

	std::shared_ptr<Input> GetInputModule();
private:
	std::shared_ptr<Input> inputModule;
};