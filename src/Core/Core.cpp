#include "Core.h"

Core::Core()
{
	sdlWindow = std::make_unique<Window>(960, 540, "SCOOT-Engine");

	// Init Time Manager

	// Init Input Manager

	// Init Camera Manager

	// Init Shader Manager

	// Init Model Manager

	// Init Scene Manager

	auto test = this->weak_from_this();
}

Core::~Core()
{

}
