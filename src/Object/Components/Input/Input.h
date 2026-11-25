#pragma once

#include <memory>
#include <utility>

#include "Managers/Event/InputModule.h"

class Input
{
public:
	explicit Input(std::shared_ptr<InputModule> inputModule)
		: inputModule(std::move(inputModule))
	{}

	bool KeyDown(SDL_Scancode key) const
	{
		return inputModule && inputModule->KeyDown(key);
	}

	bool KeyUp(SDL_Scancode key) const
	{
		return inputModule && inputModule->KeyUp(key);
	}

	bool KeyHeld(SDL_Scancode key) const
	{
		return inputModule && inputModule->KeyHeld(key);
	}

	bool KeyPressed(SDL_Scancode key) const
	{
		return inputModule && inputModule->KeyPressed(key);
	}

private:
	std::shared_ptr<InputModule> inputModule;
};
