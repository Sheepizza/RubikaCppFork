#include <RenderComponent.h>
#include <Idrawable.h>
#include <Logger.h>
#include <format>

template<typename C>
inline C* RenderComponent::AddDrawable()
{
	static_assert(std::is_base_of<IDrawable, C>::value, "Drawable must be a IDrawable");

	C* c = new C();
	drawables.push_back(c);
	return c;
}

template<typename C>
inline C* RenderComponent::GetDrawable()
{
	static_assert(std::is_base_of<IDrawable, C>::value, "Drawable must be a IDrawable");

	for (size_t i = 0; i < drawables.size(); i++)
	{
		C* drawable = dynamic_cast<C*>(drawables[i]);

		if (drawable != nullptr)
		{
			return drawable;
		}
	}

	Logger::Warning(std::format("The Drawable {} doesn't exist.", typeid(C).name()));

	return nullptr;
}
