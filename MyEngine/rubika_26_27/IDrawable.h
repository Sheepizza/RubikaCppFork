#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class IDrawable abstract
{
public:
	IDrawable(int x, int y);
	virtual ~IDrawable();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Destroy() = 0;

	bool IsVisible() const;
	void SetVisibility(bool visible);

	const sf::Transform& GetWorldTransform() const;
	void SetWorldTransform(const sf::Transform& transform);

	void Draw(sf::RenderWindow& window) const;

protected:
	bool Visible;
	sf::Transform WorldTransform;
	sf::Drawable* Drawable; // Pointer to the SFML derived class defined in IDrawable's derived class
	sf::Vector2f localPosition;
};