#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <IDrawable.h>

struct Vector2
{
	int x;
	int y;
};

class Rectangle : public IDrawable
{
public:
	sf::RectangleShape rectangle;

	Rectangle();

	void Start();
	void Update(float deltaTime);
	void Destroy();

	Vector2 limitMin;
	Vector2 limitMax;
	Vector2 direction;
};

