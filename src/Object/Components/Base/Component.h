#pragma once

#include <utility>

class IComponent
{
	public:
		virtual ~IComponent() = default;
};

template <typename T>
class ComponentModel final : public IComponent
{
	public:
	template <typename... Args>
	explicit ComponentModel(Args&&... args)
		: value(std::forward<Args>(args)...)
	{}
	T value;
};
