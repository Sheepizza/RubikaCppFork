#include "GridEntityCache.h"
#include <DynamicColliderComponent.h>

GridCacheCell::GridCacheCell()
{
}

GridCacheCell::GridCacheCell(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h)
{
}

GridEntityCache::GridEntityCache()
{
	for (size_t i = 0; i < gridSize[0]; i++)
	{
		for (size_t j = 0; j < gridSize[1]; j++)
		{
			grid[i][j] = GridCacheCell(j * 100, i * 100, cellSize[0], cellSize[1]);
		}
	}
}

GridEntityCache::~GridEntityCache()
{
}

void GridEntityCache::AddEntity(Entity* e)
{
	DynamicColliderComponent* coll = e->GetComponent<DynamicColliderComponent>();

	if (coll == nullptr)
	{
		return;
	}

	const sf::FloatRect hitbox = coll->GetHitbox();

	int posX = hitbox.position.x / 100;
	int posY = hitbox.position.y / 100;

	int sizeX = (hitbox.position.x + hitbox.size.x) / 100;
	int sizeY = (hitbox.position.y + hitbox.size.y) / 100;

	for (size_t i = posX; i <= sizeX; i++)
	{
		for (size_t j = posY; j <= sizeY; j++)
		{
			grid[i][j].Entities.push_back(e);
		}
	}
}

void GridEntityCache::RemoveEntity(Entity* e)
{
	DynamicColliderComponent* coll = e->GetComponent<DynamicColliderComponent>();

	if (coll == nullptr)
	{
		return;
	}

	const sf::FloatRect hitbox = coll->GetHitbox();

	int posX = hitbox.position.x / 100;
	int posY = hitbox.position.y / 100;

	int sizeX = (hitbox.position.x + hitbox.size.x) / 100;
	int sizeY = (hitbox.position.y + hitbox.size.y) / 100;

	for (size_t i = posX; i <= sizeX; i++)
	{
		for (size_t j = posY; j <= sizeY; j++)
		{
			auto iterator = std::find(grid[i][j].Entities.begin(), grid[i][j].Entities.end(), e);
			if (iterator != grid[i][j].Entities.end())
				grid[i][j].Entities.erase(iterator);
		}
	}
}

void GridEntityCache::GetEntities(int x, int y, std::vector<Entity*>& entities)
{
	int posX = x / 100;
	int posY = y / 100;

	entities = grid[posX][posY].Entities;
}

void GridEntityCache::GetEntities(sf::FloatRect hitbox, std::vector<Entity*>& entities)
{
	int posX = hitbox.position.x / 100;
	int posY = hitbox.position.y / 100;

	int sizeX = (hitbox.position.x + hitbox.size.x) / 100;
	int sizeY = (hitbox.position.y + hitbox.size.y) / 100;

	std::vector<Entity*> e;

	for (size_t i = posX; i <= sizeX; i++)
	{
		for (size_t j = posY; j <= sizeY; j++)
		{
			e.insert(e.end(), grid[i][j].Entities.begin(), grid[i][j].Entities.end());
		}
	}

	entities = e;
}
