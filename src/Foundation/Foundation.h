#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

class Foundation
{
public:
	Foundation();
	~Foundation();

	void SwapWindow();

private:
	SDL_Window* window{ nullptr };
};