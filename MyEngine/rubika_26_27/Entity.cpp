#include "Entity.h"
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <DynamicColliderComponent.h>
#include <Logger.h>
#include <Sprite.h>

Entity::Entity(std::string name)
{
	Name = name;
}

Entity::~Entity()
{
	for (IComponent* component : components)
	{
		delete component;
	}

	components.clear();
}

void Entity::Start()
{
	for (IComponent* component : components)
	{
		component->Start();
	}
}

void Entity::Update(float fDeltaTime)
{
	for (IComponent* component : components)
	{
		component->Update(fDeltaTime);
	}
}

void Entity::Destroy()
{
	for (IComponent* component : components)
	{
		component->Destroy();
	}

}

void Entity::Draw(sf::RenderWindow& window)
{
	RenderComponent* r = GetComponent<RenderComponent>();

	if (r != nullptr)
	{
		r->Draw(window);
	}

#ifdef _USE_IMGUI
	DynamicColliderComponent* coll = GetComponent<DynamicColliderComponent>();

	if (coll != nullptr)
	{
		coll->Draw(window);
	}
#endif
}
