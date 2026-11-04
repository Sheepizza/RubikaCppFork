#include "Obstacle.h"
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <Rectangle.h>
#include <DynamicColliderComponent.h>

Obstacle::Obstacle(sf::Vector2f position, std::string name) : Entity(name)
{
	basePosition = position;
}

Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f collSize, std::string name)
{
	basePosition = position;
	baseCollSize = collSize;

	isVisible = false;
}

Obstacle::~Obstacle()
{
}

void Obstacle::Start()
{
	TransformComponent* t = AddComponent<TransformComponent>();
	RenderComponent* r = AddComponent<RenderComponent>();

	t->SetWorldPosition(basePosition);

	StaticTile* tile = r->AddDrawable<StaticTile>(0, 0);

	if (isVisible)
	tile->SetTextureAndStaticTile("Basement", "Corner_Top_Left");

	DynamicColliderComponent* coll = AddComponent<DynamicColliderComponent>();

	if (baseCollSize == sf::Vector2f({ 0,0 }))
	{
		coll->SetHitboxSize(tile->rectangle.getSize());
	}
	else
	{
		coll->SetHitboxSize(baseCollSize);
	}

	coll->SetCollisionType(OnCollisionChoice::Block);

	Entity::Start();
}

void Obstacle::Update(float fDeltaTime)
{
	Entity::Update(fDeltaTime);
}

void Obstacle::Destroy()
{
	Entity::Destroy();
}
