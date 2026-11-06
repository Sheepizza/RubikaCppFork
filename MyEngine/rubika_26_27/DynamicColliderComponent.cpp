#include "DynamicColliderComponent.h"
#include <Entity.h>
#include <Profiler.h>

DynamicColliderComponent::DynamicColliderComponent(Entity& entity) : IComponent(entity)
{
	transformComponent = entity.GetComponent<TransformComponent>();

	if (transformComponent != nullptr)
	{
		hitbox.position = transformComponent->GetWorldPosition() + hitboxOffset;
	}
}

DynamicColliderComponent::~DynamicColliderComponent()
{
}

void DynamicColliderComponent::Start()
{
	if (transformComponent == nullptr)
	{
		transformComponent = GetEntity().GetComponent<TransformComponent>();
	}

#ifdef _USE_IMGUI
	debugHitbox.setOutlineColor(sf::Color::Green);
	debugHitbox.setOutlineThickness(1.f);
	debugHitbox.setFillColor(sf::Color::Transparent);
#endif
}

void DynamicColliderComponent::Update(float fDeltaTime)
{
	PROFILER_EVENT_BEGIN(PROFILER_COLOR_CYAN, "ColliderUpdate");
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
		PROFILER_EVENT_END();
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

void DynamicColliderComponent::SetCollisionType(OnCollisionChoice type)
{
	collisionType = type;
}

OnCollisionChoice DynamicColliderComponent::GetCollisionType()
{
	return collisionType;
}

const sf::FloatRect& DynamicColliderComponent::GetHitbox() const
{
	return hitbox;
}

void DynamicColliderComponent::SetOnCollisionCallback(std::function<OnCollisionChoice(Entity*)> callback)
{
	callbacks.push_back(callback);
}

void DynamicColliderComponent::InvokeCallbacks(Entity* other)
{
	for (auto callback : callbacks)
	{
		callback(other);
	}
}

void DynamicColliderComponent::SetCollisionFilterMask(uint8_t filter)
{
	filterMask = filter;
}

void DynamicColliderComponent::SetCollisionMode(CollisionMode mode)
{
	collisionMode = mode;
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

