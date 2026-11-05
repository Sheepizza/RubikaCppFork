#pragma once

#include <vector>
#include <Entity.h>
#include <SfML/Graphics/Rect.hpp>

struct GridCacheCell
{
	GridCacheCell();
	GridCacheCell(int _x, int _y, int _w, int _h);

	int x;
	int y;
	int w;
	int h;

	std::vector<Entity*> Entities;
};

class GridEntityCache
{
public:
	GridEntityCache();

	~GridEntityCache();

	const int gridSize[2] = { 10,10 };
	const int cellSize[2] = { 100,100 };

	GridCacheCell grid[10][10];

	void AddEntity(Entity* e);
	void RemoveEntity(Entity* e);
	void GetEntities(int x, int y, std::vector<Entity*>& entities);
	void GetEntities(sf::FloatRect hitbox, std::vector<Entity*>& entities);
};