#pragma once

#include <SDL.h>
#include <cstring>

enum class PollResponse
{
	QUIT,
	CONTINUE
};

class EventManager
{
public:
	PollResponse PollEvents();

	bool KeyDown(SDL_Scancode key) const;
	bool KeyUp(SDL_Scancode key) const;
	bool KeyHeld(SDL_Scancode key) const;
	bool KeyPressed(SDL_Scancode key) const;
private:
	Uint8 previousKeyboardState[SDL_NUM_SCANCODES]{ 0 };
	Uint8 currentKeyboardState[SDL_NUM_SCANCODES]{ 0 };
};