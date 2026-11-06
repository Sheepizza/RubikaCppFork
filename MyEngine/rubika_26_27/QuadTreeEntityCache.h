#pragma once
#include <vector>
#include <Entity.h>
#include <SFML/Graphics.hpp>

struct Quad
{
	Quad(sf::Vector2f basePos, sf::Vector2f baseSize);

	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f childSize;

	std::vector<Entity*> entities;
	Quad* quads[4];
};

class QuadTreeEntityCache
{
public:
	int depth;
	int leaf;
	sf::Vector2f treeSize;

	std::vector<Entity*> tempEntities;

	Quad* Tree;

	QuadTreeEntityCache(sf::Vector2f size);

	void AddEntity(Entity* e);

	void BuildTree();
};
