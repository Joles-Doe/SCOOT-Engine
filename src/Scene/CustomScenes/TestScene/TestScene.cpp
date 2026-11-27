#include "TestScene.h"

#include <memory>

#include "Object/CustomObjects/TestObject/TestObject.h"

void TestScene::Start()
{
	auto curuthers = std::make_shared<TestObject>();
	curuthers->AddComponent<Transform>();
	curuthers->AddComponent<Renderer>("curuthers", "curuthers");
	curuthers->AddComponent<Time>(time);
	curuthers->AddComponent<Input>(input);
	objectList.push_back(curuthers);
	curuthers->Start();


	auto curuRenderer = curuthers->TryGetComponent<Renderer>();
	curuRenderer->baseColor = glm::vec3(1.0f, 0.1f, 0.1f);
	curuRenderer->specularColor = glm::vec3(1.0f, 0.0f, 1.0f);
	curuRenderer->specularStrength = 1.0f;
	curuRenderer->shininess = 16.0f;


	auto teapot = std::make_shared<Object>();
	teapot->AddComponent<Transform>();
	//teapot->AddComponent<Renderer>("teapot", "test");
	teapot->AddComponent<Light>();
	objectList.push_back(teapot);

	teapot->TryGetComponent<Transform>()->position.x -= 2.0f;
	teapot->TryGetComponent<Transform>()->position.y += 2.0f;
	teapot->TryGetComponent<Light>()->intensity = 1.0f;
	teapot->TryGetComponent<Light>()->color = glm::vec3(0.671f, 0.0f, 1.0f);
}
