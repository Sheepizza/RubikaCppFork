#include "Rectangle.h"
#include <Logger.h>

Rectangle::Rectangle()
{
	Drawable = &rectangle;
	rectangle.setSize(sf::Vector2f(100, 100));
	rectangle.setFillColor(sf::Color::Cyan);

	limitMin = Vector2(0, 0);
	limitMax = Vector2(1000, 600);
	direction = Vector2(1, 1);
}

void Rectangle::Start()
{

}

void Rectangle::Update(float deltaTime)
{
	sf::Vector2f v2Pos = rectangle.getPosition();

	if (v2Pos.x > limitMax.x || v2Pos.x < limitMin.x)
	{
		direction.x *= -1;
	}
	if (v2Pos.y > limitMax.y || v2Pos.y < limitMin.y)
	{
		direction.y *= -1;
	}

	sf::Vector2f v(0.6 * deltaTime * direction.x, 0.85 * deltaTime * direction.y);

	rectangle.move(v);
}

void Rectangle::Destroy()
{

}