#pragma once

#include <string>
#include <IComponent.h>
#include <vector>

class TransformComponent;
class RenderComponent;

namespace sf
{
	class RenderWindow;
}

class Entity
{
public:
	std::string Name;

	Entity(std::string name = "");
	virtual ~Entity();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window);

	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent();

private:
	std::vector<IComponent*> components;
};

#include <Entity.hxx>