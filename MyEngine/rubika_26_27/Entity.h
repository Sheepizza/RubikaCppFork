#pragma once

#include <string>
#include <IComponent.h>
#include <vector>

#define ENTITY_TAG_NONE			0
#define ENTITY_TAG_STATIC		1 << 0
#define ENTITY_TAG_DYNAMIC		1 << 1
#define ENTITY_TAG_NEUTRAL		1 << 2
#define ENTITY_TAG_ENEMY		1 << 3
#define ENTITY_TAG_PLAYER		1 << 4

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

	void AdjustPosition(Entity* e);
	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window);

	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent();

	void AddTag(uint8_t tag);

	void Remove(uint8_t tag);

	bool HasTag(uint8_t tag);

	bool HasPartialTag(uint8_t tag);

private:
	std::vector<IComponent*> components;

	uint8_t tags;
};

#include <Entity.hxx>