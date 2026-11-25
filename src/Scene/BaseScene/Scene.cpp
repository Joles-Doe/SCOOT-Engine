#include "Scene.h"

#include <utility>

Scene::Scene(std::shared_ptr<TimeModule> timeModule, std::shared_ptr<InputModule> inputModule)
	: time(std::move(timeModule)), input(std::move(inputModule))
{}

std::vector<std::shared_ptr<Object>>& Scene::GetObjects()
{
    return objectList;
}

void Scene::UpdateObjects()
{
	for (const auto& object : objectList)
	{
		if (object)
			object->Update();
	}
}
