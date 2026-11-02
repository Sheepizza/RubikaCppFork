#include "Entity.h"
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <Logger.h>
#include <Sprite.h>

Entity::Entity(std::string name)
{
	Name = name;
}

Entity::~Entity()
{
	//delete GetComponent<RenderComponent>();
	//delete GetComponent<TransformComponent>();
}

void Entity::Start()
{
}

void Entity::Update(float fDeltaTime)
{
	TransformComponent* t = GetComponent<TransformComponent>();

	if (t != nullptr)
	{
		t->Update(fDeltaTime);
	}

	RenderComponent* r = GetComponent<RenderComponent>();

	if (r != nullptr)
	{
		r->Update(fDeltaTime);
	}
}

void Entity::Destroy()
{

}

void Entity::Move(float x, float y)
{
	TransformComponent* t = GetComponent<TransformComponent>();

	if (t != nullptr)
	{
		t->SetWorldPosition({ t->GetWorldPosition().x + x, t->GetWorldPosition().y + y });
	}
}

void Entity::Draw(sf::RenderWindow& window)
{
	RenderComponent* r = GetComponent<RenderComponent>();

	if (r == nullptr)
	{
		//Logger::Warning(std::format("Failed to draw {}, Render Component is null", Name));
		return;
	}

	r->Draw(window);
}
