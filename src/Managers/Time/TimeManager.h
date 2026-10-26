#pragma once

#include <SDL.h>
#include <memory>

#include "Time.h"

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	std::shared_ptr<Time> GetTimeModule();

	void PreframeUpdate();
	void ProcessAccumulator();
	void SubtractAccumulator();

	bool DoPhysicsUpdate();
private:
	std::shared_ptr<Time> timeModule;

	double accumulator{ 0 };
	double fixedDeltaTimeCap{ 1 / 60 };
	double maxFrameTime{ 0.25 };

	Uint64 performanceFrequency{ 0 };
	Uint64 previousCounter{ 0 };
	double currentDeltaTime{ 0 };

	//todo - maybe implement an alpha for physics? (accumulator / fixedDeltaTimeCap)
};