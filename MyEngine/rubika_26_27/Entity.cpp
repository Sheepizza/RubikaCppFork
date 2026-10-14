#include "Entity.h"

Entity::Entity(std::string name) : Transform(*this), Render(*this)
{
	Name = name;
}

Entity::~Entity()
{

}

void Entity::Start()
{

}

void Entity::Update(float fDeltaTime)
{
	Render.rectangle.Update(fDeltaTime);
}

void Entity::Destroy()
{

}

void Entity::Draw(sf::RenderWindow& window) const
{
	Render.rectangle.Draw(window);
}
