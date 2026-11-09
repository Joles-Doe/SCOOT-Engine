#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

class Window
{
public:
	Window(int windowWidth, int windowHeight, const char* windowName);
	~Window();

	void SwapWindow();

	std::pair<int, int> GetSize();

private:
	SDL_Window* window{ nullptr };
};