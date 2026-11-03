#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(std::string name = "Player");
	~Player();

	virtual void Start() override;
	virtual void Update(float fDeltaTime) override;
	virtual void Destroy() override;

	void Move(float x, float y);
};

