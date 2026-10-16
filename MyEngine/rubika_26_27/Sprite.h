#pragma once

#include <SFML/Graphics.hpp>
#include <IDrawable.h>

class Sprite : public IDrawable
{
public:

	sf::Sprite sprite;
	sf::Texture texture;

	Sprite();

	void Start();
	void Update(float deltaTime);
	void Destroy();
};

