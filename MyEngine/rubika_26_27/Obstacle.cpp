#include "Obstacle.h"
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <Rectangle.h>
#include <DynamicColliderComponent.h>

Obstacle::Obstacle(sf::Vector2f position, std::string name) : Entity(name)
{
	basePosition = position;
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
	tile->SetTextureAndStaticTile("Basement", "Corner_Top_Left");

	DynamicColliderComponent* coll = AddComponent<DynamicColliderComponent>();
	coll->SetHitboxSize(tile->rectangle.getSize());

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
