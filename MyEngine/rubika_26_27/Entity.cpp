#include "Entity.h"

Entity::Entity(std::string name)
{
	Name = name;
	Transform = TransformComponent();
}

Entity::~Entity()
{

}

void Entity::Start()
{

}

void Entity::Update(float fDeltaTime)
{

}

void Entity::Destroy()
{

}

void Entity::Draw(sf::RenderWindow& window) const
{
}
