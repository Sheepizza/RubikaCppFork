#include "RenderComponent.h"
#include <Entity.h>
#include <TransformComponent.h>

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
	TransformComponent* t = GetEntity().GetComponent<TransformComponent>();

	for (size_t i = 0; i < drawables.size(); i++)
	{
		if (t != nullptr)
		{
			drawables[i]->SetWorldTransform(t->GetMatrix());
		}

		drawables[i]->Update(fDeltaTime);
	}
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