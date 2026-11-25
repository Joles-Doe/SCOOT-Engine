#pragma once

#include <SDL.h>

class TimeManager;

class TimeModule
{
public:
	float DeltaTime();
	float FixedDeltaTime();

private:
	void SetDeltaTime(double incomingDeltaTime);
	void SetFixedDeltaTime(double incomingFixedDeltaTime);

	double deltaTime{ 0 };
	double fixedDeltaTime{ 0 };

	friend class TimeManager;
};