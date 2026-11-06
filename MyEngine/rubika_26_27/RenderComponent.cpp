#include "RenderComponent.h"
#include <Entity.h>
#include <TransformComponent.h>
#include <Profiler.h>

RenderComponent::RenderComponent(Entity& entity) : IComponent(entity)
{
}

RenderComponent::~RenderComponent()
{
	for (IDrawable* drawable : drawables)
	{
		delete drawable;
	}

	drawables.clear();
}

void RenderComponent::Start()
{
	transformComponent = GetEntity().GetComponent<TransformComponent>();

	for (IDrawable* drawable : drawables)
	{
		if (transformComponent != nullptr)
		{
			drawable->SetWorldTransform(transformComponent->GetMatrix());
		}
	}

	for (IDrawable* drawable : drawables)
	{
		drawable->Start();
	}
}

void RenderComponent::Update(float fDeltaTime)
{
	PROFILER_EVENT_BEGIN(PROFILER_COLOR_ORANGE, "RenderUpdate");
	if (transformComponent == nullptr)
	{
		transformComponent = GetEntity().GetComponent<TransformComponent>();
	}

	for (IDrawable* drawable : drawables)
	{
		if (transformComponent != nullptr)
		{
			drawable->SetWorldTransform(transformComponent->GetMatrix());
		}
		drawable->Update(fDeltaTime);
	}
	PROFILER_EVENT_END();
}

void RenderComponent::Destroy()
{}

void RenderComponent::Draw(sf::RenderWindow& window)
{
	for (IDrawable* drawable : drawables)
	{
		drawable->Draw(window);
	}
}