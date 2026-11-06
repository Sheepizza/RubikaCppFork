#include "QuadTreeEntityCache.h"
#include <DynamicColliderComponent.h>

Quad::Quad(sf::Vector2f basePos, sf::Vector2f baseSize) : position(basePos), size(baseSize)
{
	childSize = { size.x / 2, size.y / 2 };
}

QuadTreeEntityCache::QuadTreeEntityCache(sf::Vector2f size) : treeSize(size)
{
}

void QuadTreeEntityCache::AddEntity(Entity* e)
{
	if (Tree == nullptr)
	{
		tempEntities.push_back(e);
		return;
	}

	DynamicColliderComponent* coll = e->GetComponent<DynamicColliderComponent>();

	if (coll == nullptr)
	{
		return;
	}

	const sf::FloatRect hitbox = coll->GetHitbox();

	int cornerTopLeftX = hitbox.position.x;
	int cornerTopLeftY = hitbox.position.y;

	int cornerBotRightX = (hitbox.position.x + hitbox.size.x);
	int cornerBotLeftY = (hitbox.position.y + hitbox.size.y);

	for (Quad* quad : Tree->quads)
	{
		
	}
}

void QuadTreeEntityCache::BuildTree()
{
	Tree = new Quad( { 0,0 } , treeSize);

	Tree->quads[0] = new Quad({ 0,0 }, Tree->childSize);
	Tree->quads[1] = new Quad({ Tree->size.x / 2,0 }, Tree->childSize);
	Tree->quads[2] = new Quad({ 0,Tree->size.y / 2 }, Tree->childSize);
	Tree->quads[3] = new Quad({ Tree->size.x / 2,Tree->size.y / 2 }, Tree->childSize);

	for (Entity* e : tempEntities)
	{
		AddEntity(e);
	}

	tempEntities.clear();
}
