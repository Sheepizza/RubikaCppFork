#pragma once

#include <IComponent.h>
#include <vector>
#include <IDrawable.h>
#include <TransformComponent.h>

class RenderComponent : public IComponent
{
public:
	RenderComponent(Entity& entity);
	~RenderComponent();

	void Start();
	void Update(float fDeltaTime);
	void Destroy();
	void Draw(sf::RenderWindow& window);

	template <typename C>
	C* AddDrawable(int x, int y);

	template <typename C>
	C* GetDrawable();

	TransformComponent* transformComponent;

private:
	std::vector<IDrawable*> drawables;
};

#include <RenderComponent.hxx>

