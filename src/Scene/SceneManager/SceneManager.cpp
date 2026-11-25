#include "SceneManager.h"

#include <utility>

SceneManager::SceneManager(std::shared_ptr<TimeModule> timeModule,
	std::shared_ptr<InputModule> inputModule)
{
	// Register all of the scenes
	Register(SceneID::DEFAULT, [timeModule, inputModule] {
		return std::make_unique<TestScene>(timeModule, inputModule);
		});

	Load(SceneID::DEFAULT);
}

void SceneManager::Load(SceneID id)
{
	auto it = factories.find(id);
	if (it == factories.end()) throw std::runtime_error("Scene not found");

	currentScene = it->second();
	currentScene->Start();
}

std::vector<std::shared_ptr<Object>>& SceneManager::GetObjects()
{
	return currentScene->GetObjects();
}

void SceneManager::UpdateObjects()
{
	currentScene->UpdateObjects();
}

void SceneManager::Register(SceneID id, SceneFactory factory)
{
	factories[id] = std::move(factory);
}
