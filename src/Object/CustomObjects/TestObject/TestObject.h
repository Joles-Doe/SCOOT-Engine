#pragma once

#include "Object/Object.h"

class TestObject : public Object
{
public:
	using Object::Object;

	void Start() override;
	void Update() override;

private:
	Time* timeComponent;
	Input* inputComponent;

	float rotation{ 0.0f };
	float rotationSpeed{ 2.0f };
};