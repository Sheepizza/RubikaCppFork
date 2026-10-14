#pragma once

#include <IComponent.h>
#include <Rectangle.h>

class RenderComponent : public IComponent
{
public:
	RenderComponent(Entity& entity);
	~RenderComponent();

	void Start();
	void Update(float fDeltaTime);
	void Destroy();

	Rectangle rectangle;
};

