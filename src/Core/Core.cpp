#include "Core.h"

Core::Core()
{
	sdlWindow = std::make_shared<Window>(960, 540, "SCOOT-Engine");

	timeManager = std::make_unique<TimeManager>();

	eventManager = std::make_unique<EventManager>();

	renderManager = std::make_unique<RenderManager>(sdlWindow);

	sceneManager = std::make_unique<SceneManager>(timeManager->GetTimeModule(), eventManager->GetInputModule());

	// Init Camera Manager

	// HUD Manager
	
	// Audio Manager

	//auto test = this->weak_from_this();
}

Core::~Core()
{

}

void Core::Update()
{
	timeManager->PreframeUpdate();

	PollResponse pollEvents = eventManager->PollEvents();
	if (pollEvents != PollResponse::CONTINUE)
	{
		// User has quit
		quit = true;
	}

	timeManager->ProcessAccumulator();
	while (timeManager->DoPhysicsUpdate())
	{
		// update physics
		timeManager->SubtractAccumulator();
	}

	sceneManager->UpdateObjects();

	//rendering
	renderManager->DrawObjects(sceneManager->GetObjects());

	// Going for an uncapped frame rate for the time being - subject to change
	//timeManager->PostframeUpdate();
}

bool Core::QuitProgram()
{
	return quit;
}
