#pragma once

#include <memory>
#include <vector>

#include "Managers/Time/TimeModule.h"
#include "Managers/Event/InputModule.h"
#include "Object/Object.h"

class Scene
{
public:
	Scene(std::shared_ptr<TimeModule> timeModule, std::shared_ptr<InputModule> inputModule);

	virtual void Start() = 0;

	std::vector<std::shared_ptr<Object>>& GetObjects();

	void UpdateObjects();
protected:
	std::shared_ptr<TimeModule> time;
	std::shared_ptr<InputModule> input;

	std::vector<std::shared_ptr<Object>> objectList;
};
