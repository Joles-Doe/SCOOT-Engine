#include "TimeModule.h"

float TimeModule::DeltaTime()
{
	return static_cast<float>(deltaTime);
}

float TimeModule::FixedDeltaTime()
{
	return static_cast<float>(fixedDeltaTime);
}

void TimeModule::SetDeltaTime(double incomingDeltaTime)
{
	deltaTime = incomingDeltaTime;
}

void TimeModule::SetFixedDeltaTime(double incomingFixedDeltaTime)
{
	fixedDeltaTime = incomingFixedDeltaTime;
}
