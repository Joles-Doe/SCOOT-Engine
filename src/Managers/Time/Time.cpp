#include "Time.h"

float Time::DeltaTime()
{
	return static_cast<float>(deltaTime);
}

float Time::FixedDeltaTime()
{
	return static_cast<float>(fixedDeltaTime);
}

void Time::SetDeltaTime(double incomingDeltaTime)
{
	deltaTime = incomingDeltaTime;
}

void Time::SetFixedDeltaTime(double incomingFixedDeltaTime)
{
	fixedDeltaTime = incomingFixedDeltaTime;
}
