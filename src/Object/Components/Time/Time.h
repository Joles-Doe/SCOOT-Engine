#pragma once

#include <memory>
#include <utility>

#include "Managers/Time/TimeModule.h"

class Time
{
public:
	explicit Time(std::shared_ptr<TimeModule> timeModule)
		: timeModule(std::move(timeModule))
	{}

	float DeltaTime() const
	{
		return timeModule ? timeModule->DeltaTime() : 0.0f;
	}

	float FixedDeltaTime() const
	{
		return timeModule ? timeModule->FixedDeltaTime() : 0.0f;
	}

private:
	std::shared_ptr<TimeModule> timeModule;
};
