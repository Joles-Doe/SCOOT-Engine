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
}
