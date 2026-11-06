#include "Player.h"
#include <TransformComponent.h>
#include <DynamicColliderComponent.h>
#include <RenderComponent.h>
#include <Sprite.h>
#include <Profiler.h>
#include <Globals.h>
#include <SceneMgr.h>

Player::Player(std::string name) : Entity(name)
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

	AddTag(ENTITY_TAG_DYNAMIC | ENTITY_TAG_PLAYER);

	coll->SetCollisionMode(CollisionMode::Partial);

	coll->SetCollisionFilterMask(ENTITY_TAG_STATIC);
}

Player::~Player()
{
}

void Player::Start()
{
	Entity::Start();
}

void Player::Update(float fDeltaTime)
{
	PROFILER_EVENT_BEGIN(PROFILER_COLOR_PINK, "PlayerUpdate");
	Entity::Update(fDeltaTime);
	PROFILER_EVENT_END();
}

void Player::Destroy()
{
	Entity::Destroy();
}

void Player::Move(float x, float y)
{
	gData.SceneMgr->ActiveScene->DynamicGridCache.RemoveEntity(dynamic_cast<Entity*>(this));

	TransformComponent* t = GetComponent<TransformComponent>();

	sf::Vector2f direction{ x,y };

	sf::Vector2f force = direction.normalized();

	force *= 0.1f;

	force += t->GetWorldPosition();

	if (t != nullptr)
	{
		t->SetWorldPosition({ force });
	}

	gData.SceneMgr->ActiveScene->DynamicGridCache.AddEntity(dynamic_cast<Entity*>(this));
}
