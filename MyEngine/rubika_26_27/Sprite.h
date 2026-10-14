#pragma once

#include <SFML/Graphics.hpp>
#include <IDrawable.h>

class Sprite : public IDrawable
{
public:
	sf::Sprite sprite;

	void Start();
	void Update(float deltaTime);
	void Destroy();
};

