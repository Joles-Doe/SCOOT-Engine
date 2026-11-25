#include "TestObject.h"

void TestObject::Start()
{
	timeComponent = TryGetComponent<Time>();
	inputComponent = TryGetComponent<Input>();
}

void TestObject::Update()
{
	rotation += rotationSpeed * timeComponent->FixedDeltaTime();

	if (rotation >= 360) rotation = 0;

	TryGetComponent<Transform>()->rotation.y = rotation;
}
