#include "Entity.h"
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <Logger.h>

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
	RenderComponent* r = GetComponent<RenderComponent>();

	if (r == nullptr)
	{
		Logger::Warning(std::format("Failed to update {}, Render Component is null", Name));
		return;
	}
}

void Entity::Destroy()
{

}

void Entity::Draw(sf::RenderWindow& window)
{
	RenderComponent* r = GetComponent<RenderComponent>();

	if (r == nullptr)
	{
		Logger::Warning(std::format("Failed to draw {}, Render Component is null", Name));
		return;
	}

	r->Draw(window);
}
