#include "TimeManager.h"

TimeManager::TimeManager()
{
	timeModule = std::make_shared<TimeModule>();

	performanceFrequency = SDL_GetPerformanceFrequency();
	previousCounter = SDL_GetPerformanceCounter();

	timeModule->SetFixedDeltaTime(fixedDeltaTimeCap);
}

TimeManager::~TimeManager()
{
	timeModule.reset();
}

std::shared_ptr<TimeModule> TimeManager::GetTimeModule()
{
	return timeModule;
}

void TimeManager::PreframeUpdate()
{
	const Uint64 currentCounter = SDL_GetPerformanceCounter();

	currentDeltaTime = static_cast<double>(currentCounter - previousCounter) / static_cast<double>(performanceFrequency);
	currentDeltaTime = std::min(currentDeltaTime, maxFrameTime);

	previousCounter = currentCounter;

	timeModule->SetDeltaTime(currentDeltaTime);
}

void TimeManager::ProcessAccumulator()
{
	accumulator += currentDeltaTime;
}

void TimeManager::SubtractAccumulator()
{
	accumulator -= fixedDeltaTimeCap;
}

bool TimeManager::DoPhysicsUpdate()
{
	return accumulator >= fixedDeltaTimeCap;
}
