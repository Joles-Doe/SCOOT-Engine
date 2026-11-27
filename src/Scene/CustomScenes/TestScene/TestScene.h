#pragma once

#include "Scene/BaseScene/Scene.h"

#include "Object/Object.h"
#include "Object/Components/Base/Component.h"
#include "Object/Components/Transform/Transform.h"
#include "Object/Components/Renderer/Renderer.h"
#include "Object/Components/Input/Input.h"
#include "Object/Components/Time/Time.h"
#include "Object/Components/Light/Light.h"

class TestScene : public Scene
{
public:
	using Scene::Scene;

	void Start() override;

private:

};
