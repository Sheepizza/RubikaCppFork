#include "RenderComponent.h"

RenderComponent::RenderComponent(Entity& entity) : IComponent(entity)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Start()
{}

void RenderComponent::Update(float fDeltaTime)
{
}

void RenderComponent::Destroy()
{}

void RenderComponent::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < drawables.size(); i++)
	{

		drawables[i]->Draw(window);
	}
}