#pragma once

#include <SDL.h>
#include <cstring>

class EventManager;

class InputModule
{
public:
	bool KeyDown(SDL_Scancode key) const;
	bool KeyUp(SDL_Scancode key) const;
	bool KeyHeld(SDL_Scancode key) const;
	bool KeyPressed(SDL_Scancode key) const;
private:
	Uint8 previousKeyboardState[SDL_NUM_SCANCODES]{ 0 };
	Uint8 currentKeyboardState[SDL_NUM_SCANCODES]{ 0 };

	friend class EventManager;
};