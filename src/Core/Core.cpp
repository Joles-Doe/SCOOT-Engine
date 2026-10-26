#include "Core.h"

Core::Core()
{
	sdlWindow = std::make_unique<Window>(960, 540, "SCOOT-Engine");

	timeManager = std::make_unique<TimeManager>();

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

void Core::Update()
{
	// core stuff

	timeManager->PreframeUpdate();

	// process input

	timeManager->ProcessAccumulator();
	while (timeManager->DoPhysicsUpdate())
	{
		// update physics
		timeManager->SubtractAccumulator();
	}

	// update

	//rendering

	// Going for an uncapped frame rate for the time being - subject to change
	//timeManager->PostframeUpdate();
}
