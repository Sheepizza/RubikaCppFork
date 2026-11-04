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

void Entity::AdjustPosition(Entity* e)
{
	TransformComponent* t = GetComponent<TransformComponent>();

	DynamicColliderComponent* coll = GetComponent<DynamicColliderComponent>();
	DynamicColliderComponent* otherColl = e->GetComponent<DynamicColliderComponent>();

	const sf::FloatRect* hitbox = &coll->GetHitbox();
	const sf::FloatRect* otherHitbox = &otherColl->GetHitbox();

	float distanceX = hitbox->getCenter().x - otherHitbox->getCenter().x;
	float distanceY = hitbox->getCenter().y - otherHitbox->getCenter().y;

	sf::Vector2f newPos;
	
	sf::FloatRect overlap = hitbox->findIntersection(*otherHitbox).value();

	if (std::abs(overlap.size.x) < std::abs(overlap.size.y))
	{
		if (distanceX < 0)
		{
			newPos.x = otherHitbox->position.x - hitbox->size.x;
			newPos.y = t->GetWorldPosition().y;
		}
		else
		{
			newPos.x = otherHitbox->position.x + otherHitbox->size.x;
			newPos.y = t->GetWorldPosition().y;
		}
	}
	else
	{
		if (distanceY < 0)
		{
			newPos.y = otherHitbox->position.y - hitbox->size.y;
			newPos.x = t->GetWorldPosition().x;
		}
		else
		{
			newPos.y = otherHitbox->position.y + otherHitbox->size.y;
			newPos.x = t->GetWorldPosition().x;
		}
	}

	t->SetWorldPosition(newPos);
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
