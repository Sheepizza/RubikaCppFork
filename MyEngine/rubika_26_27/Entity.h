#pragma once

#include <string>
#include "TransformComponent.h"
#include "RenderComponent.h"

namespace sf
{
	class RenderWindow;
}

class Entity
{
public:
	std::string Name;
	TransformComponent Transform;
	RenderComponent Render;

	Entity(std::string name = "");
	virtual ~Entity();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;
};
