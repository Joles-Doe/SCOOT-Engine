#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Components/Base/Component.h"
#include "Object/Components/Base/Component.h"
#include "Object/Components/Transform/Transform.h"
#include "Object/Components/Renderer/Renderer.h"
#include "Object/Components/Input/Input.h"
#include "Object/Components/Time/Time.h"

class Object : public std::enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object() = default;

	template <typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		auto component = std::make_shared<ComponentModel<T>>(
			std::forward<Args>(args)...);
		T& result = component->value;
		components.push_back(std::move(component));
		return result;
	}

	template <typename T>
	T* TryGetComponent()
	{
		for (const auto& component : components)
		{
			if (auto* model = dynamic_cast<ComponentModel<T>*>(component.get()))
				return &model->value;
		}

		return nullptr;
	}

	virtual void Start();

	virtual void Update();
private:
	std::vector<std::shared_ptr<IComponent>> components;

	bool hasStarted{ false };
};
