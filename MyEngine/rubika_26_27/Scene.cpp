#include "Scene.h"
#include "Logger.h"
#include <DynamicColliderComponent.h>

Scene::Scene(const std::string& name)
{
	Name = name;
}

Scene::~Scene()
{
}

void Scene::AddEntity(Entity* entity) 
{
	Logger::Info(std::format("Entity {} loaded in {}.", entity->Name, Name));
	Entities.push_back(entity);

	if (entity->HasTag(ENTITY_TAG_DYNAMIC))
	{
		DynamicGridCache.AddEntity(entity);
	}
	else if (entity->HasTag(ENTITY_TAG_STATIC))
	{
		StaticGridCache.AddEntity(entity);
	}
}

void Scene::RemoveEntity(Entity* entity) 
{
	for (size_t i = 0; i < Entities.size(); i++)
	{
		if (&entity == &Entities[i]) 
		{
			Entities[i]->Destroy();
			Entities.erase(Entities.begin() + i);
			return;
		}
	}

	Logger::Error("Entity not in range.");
}

void Scene::CreateEntity(char* input)
{
	if (!input[0])
	{
		Logger::Warning("You didn't give a name to the entity.");
		return;
	}

	Entity* entity = new Entity(input);
	AddEntity(entity);
	entity->Start();
}


std::string Scene::GetEntities()
{
	std::string text;

	if (Entities.size() == 0)
	{
		text = "No entity.";
	}

	for (Entity* entity : Entities)
	{
		text += entity->Name + " ";
	}

	return text;
}

void Scene::Draw(sf::RenderWindow& window) const
{
	for (Entity* entity : Entities)
	{
		entity->Draw(window);
	}
}

void Scene::Start() 
{
	for (Entity* entity : Entities)
	{
		entity->Start();
	}
}

void Scene::Update(float fDeltaTime)
{
	for (Entity* entity : Entities)
	{
		entity->Update(fDeltaTime);
	}

	CheckCollisions();
}

void Scene::Destroy() 
{
	for (size_t i = Entities.size() - 1; i > 0; i--)
	{
		Entities[i]->Destroy();
		Entities.pop_back();
	}

	Entities.clear();
}

void Scene::CheckCollisions()
{
	auto dynamicGrid = DynamicGridCache.grid;

	auto staticGrid = StaticGridCache.grid;

	for (size_t i = 0; i < DynamicGridCache.gridSize[0]; i++)
	{
		for (size_t j = 0; j < DynamicGridCache.gridSize[1]; j++)
		{
			for (Entity* e : dynamicGrid[i][j].Entities)
			{
				DynamicColliderComponent* coll = e->GetComponent<DynamicColliderComponent>();

				if (coll == nullptr)
				{
					continue;
				}

				if (!coll->AreCollisionsEnabled())
				{
					continue;
				}

				for (Entity* e2 : staticGrid[i][j].Entities)
				{
					DynamicColliderComponent* coll2 = e2->GetComponent<DynamicColliderComponent>();

					if (coll2 == nullptr || coll2 == coll)
					{
						continue;
					}

					if (!coll2->AreCollisionsEnabled())
					{
						continue;
					}

					if (coll->collisionMode == CollisionMode::Complete)
					{
						if (!e2->HasTag(coll->filterMask))
						{
							return;
						}
					}
					else
					{
						if (!e2->HasPartialTag(coll->filterMask))
						{
							return;
						}
					}

					if (coll->GetHitbox().findIntersection(coll2->GetHitbox()))
					{
						coll->InvokeCallbacks(e2);
						coll2->InvokeCallbacks(e);
					}
				}
			}
		}
	}

	/*for (Entity* e : DynamicEntities)
	{
		DynamicColliderComponent* coll = e->GetComponent<DynamicColliderComponent>();

		if (coll == nullptr)
		{
			continue;
		}

		if (!coll->AreCollisionsEnabled())
		{
			continue;
		}

		for (Entity* e2 : StaticEntities)
		{
			DynamicColliderComponent* coll2 = e2->GetComponent<DynamicColliderComponent>();

			if (coll2 == nullptr || coll2 == coll)
			{
				continue;
			}

			if (!coll2->AreCollisionsEnabled())
			{
				continue;
			}

			if (coll->collisionMode == CollisionMode::Complete)
			{
				if (!e2->HasTag(coll->filterMask))
				{
					return;
				}
			}
			else
			{
				if (!e2->HasPartialTag(coll->filterMask))
				{
					return;
				}
			}

			if (coll->GetHitbox().findIntersection(coll2->GetHitbox()))
			{
				coll->InvokeCallbacks(e2);
				coll2->InvokeCallbacks(e);
			}
		}

	}*/
}
