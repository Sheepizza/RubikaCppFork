#pragma once
#include "Entity.h"
#include <SFML/System/Vector2.hpp>

class Obstacle : public Entity
{
public:
	Obstacle(sf::Vector2f position, std::string name = "Obstacle");
	~Obstacle();

	virtual void Start() override;
	virtual void Update(float fDeltaTime) override;
	virtual void Destroy() override;

	sf::Vector2f basePosition;
};

