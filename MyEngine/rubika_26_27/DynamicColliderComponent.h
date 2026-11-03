#pragma once

#include <IComponent.h>
#include <TransformComponent.h>

#include <SfML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

enum class OnCollisionChoice
{
	Ignore,
	Block,
};

class DynamicColliderComponent : public IComponent
{
public:
	sf::FloatRect hitbox;
	sf::Vector2f hitboxOffset;

	bool canCollide = true;

	TransformComponent* transformComponent;

	std::vector<std::function<OnCollisionChoice(const Entity*)>> callbacks;

	DynamicColliderComponent(Entity& entity);
	~DynamicColliderComponent();

	virtual void Start() override;
	virtual void Update(float fDeltaTime) override;
	virtual void Destroy() override;

	void SetHitboxSize(sf::Vector2f size);
	void SetHitboxOffset(sf::Vector2f offset);

	void EnableCollision(bool bEnable);
	bool AreCollisionsEnabled() const;

	const sf::FloatRect& GetHitbox() const;

	void SetOnCollisionCallback(std::function<OnCollisionChoice(const Entity*)> callback);

	void InvokeCallbacks();

#ifdef _USE_IMGUI
	sf::RectangleShape debugHitbox;
	bool canDrawDebug = false;
	
	void DisplayColliders(bool enable);
	void Draw(sf::RenderWindow& window);
#endif
};