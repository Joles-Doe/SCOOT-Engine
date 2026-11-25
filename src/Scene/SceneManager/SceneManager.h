#pragma once

#include <memory>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "Managers/Time/TimeModule.h"
#include "Managers/Event/InputModule.h"

#include "Object/Object.h"
#include "Scene/SceneIDs.h"
#include "Scene/BaseScene/Scene.h"

#include "Scene/CustomScenes/TestScene/TestScene.h"

using SceneFactory = std::function<std::unique_ptr<Scene>()>;

class SceneManager
{
public:
	SceneManager(std::shared_ptr<TimeModule> timeModule,
		std::shared_ptr<InputModule> inputModule);

	void Load(SceneID id);

	std::vector<std::shared_ptr<Object>>& GetObjects();
	void UpdateObjects();

private:
	void Register(SceneID id, SceneFactory factory);

	std::unordered_map<SceneID, SceneFactory> factories;
	std::unique_ptr<Scene> currentScene;
};
