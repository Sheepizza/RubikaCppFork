#include "Scene.h"
#include "Logger.h"

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
