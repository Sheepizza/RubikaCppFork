#include "DynamicColliderComponent.h"
#include <Entity.h>

DynamicColliderComponent::DynamicColliderComponent(Entity& entity) : IComponent(entity)
{
}

DynamicColliderComponent::~DynamicColliderComponent()
{
}

void DynamicColliderComponent::Start()
{
	transformComponent = GetEntity().GetComponent<TransformComponent>();

#ifdef _USE_IMGUI
	debugHitbox.setOutlineColor(sf::Color::Green);
	debugHitbox.setOutlineThickness(1.f);
	debugHitbox.setFillColor(sf::Color::Transparent);
#endif
}

void DynamicColliderComponent::Update(float fDeltaTime)
{
	if (transformComponent == nullptr)
	{
		transformComponent = GetEntity().GetComponent<TransformComponent>();
	}

	if (transformComponent != nullptr)
	{
		hitbox.position = transformComponent->GetWorldPosition() + hitboxOffset;

#ifdef _USE_IMGUI
		debugHitbox.setPosition(transformComponent->GetWorldPosition() + hitboxOffset);
#endif
	}
}

void DynamicColliderComponent::Destroy()
{
}

void DynamicColliderComponent::SetHitboxSize(sf::Vector2f size)
{
	hitbox.size = size;

#ifdef _USE_IMGUI
	debugHitbox.setSize(size);
#endif
}

void DynamicColliderComponent::SetHitboxOffset(sf::Vector2f offset)
{
	hitboxOffset = offset;
}

void DynamicColliderComponent::EnableCollision(bool bEnable)
{
	canCollide = bEnable;
}

bool DynamicColliderComponent::AreCollisionsEnabled() const
{
	return canCollide;
}

const sf::FloatRect& DynamicColliderComponent::GetHitbox() const
{
	return hitbox;
}

void DynamicColliderComponent::SetOnCollisionCallback(std::function<OnCollisionChoice(const Entity*)> callback)
{
	callbacks.push_back(callback);
}

void DynamicColliderComponent::InvokeCallbacks()
{
	for (auto callback : callbacks)
	{
		callback(&GetEntity());
	}
}

void DynamicColliderComponent::DisplayColliders(bool enable)
{
	canDrawDebug = enable;
}

void DynamicColliderComponent::Draw(sf::RenderWindow& window)
{
	if (canDrawDebug)
	{
		window.draw(debugHitbox);
	}
}

