#pragma once

#include <memory>

#include "Window/Window.h"

class Core : public std::enable_shared_from_this<Core>
{
public:
	Core();
	~Core();
private:
	std::unique_ptr<Window> sdlWindow;
};