#include "Player.h"
#include <TransformComponent.h>
#include <DynamicColliderComponent.h>
#include <RenderComponent.h>
#include <Sprite.h>

Player::Player(std::string name) : Entity(name)
{
}

Player::~Player()
{
}

void Player::Start()
{
	TransformComponent* t = AddComponent<TransformComponent>();

	DynamicColliderComponent* coll = AddComponent<DynamicColliderComponent>();

	coll->SetHitboxSize({ 28, 40 });

	std::function<OnCollisionChoice(Entity*)> callback = [this, coll](Entity* e) -> OnCollisionChoice
		{
			AdjustPosition(e); 
			return coll->GetCollisionType();
		};

	coll->SetOnCollisionCallback(callback);

	t->SetWorldPosition({ 100,100 });

	RenderComponent* r = AddComponent<RenderComponent>();

	Sprite* body = r->AddDrawable<Sprite>(5, 21);

	body->SetTextureAndSprite("IsaacSprite", "Body_Vertical");

	Sprite* head = r->AddDrawable<Sprite>(0, 0);

	head->SetTextureAndSprite("IsaacSprite", "Head_Down");

	Entity::Start();
}

void Player::Update(float fDeltaTime)
{
	Entity::Update(fDeltaTime);
}

void Player::Destroy()
{
	Entity::Destroy();
}

void Player::Move(float x, float y)
{
	TransformComponent* t = GetComponent<TransformComponent>();

	sf::Vector2f direction{ x,y };

	sf::Vector2f force = direction.normalized();

	force *= 0.1f;

	force += t->GetWorldPosition();

	if (t != nullptr)
	{
		t->SetWorldPosition({ force });
	}
}
