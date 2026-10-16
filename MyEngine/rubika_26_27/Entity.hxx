#include <Entity.h>
#include <IComponent.h>
#include <Logger.h>
#include <format>

template<typename C>
inline C* Entity::AddComponent()
{
	static_assert(std::is_base_of<IComponent, C>::value, "Component must be a IComponent");

	for (size_t i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<C*>(components[i]) != nullptr)
		{
			Logger::Warning(std::format("The Component {} already exist in {}.", typeid(C).name(), Name));
			return nullptr;
		}
	}

	C* c = new C(*this);
	components.push_back(c);
	return c;
}

template<typename C>
inline C* Entity::GetComponent()
{
	static_assert(std::is_base_of<IComponent, C>::value, "Component must be a IComponent");

	for (size_t i = 0; i < components.size(); i++)
	{
		C* component = dynamic_cast<C*>(components[i]);

		if (component != nullptr)
		{
			return component;
		}
	}

	Logger::Warning(std::format("The Component {} doesn't exist in {}.", typeid(C).name(), Name));
	return nullptr;
}
