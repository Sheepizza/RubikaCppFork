#pragma once

#include <DebugMgr.h>
#include "Scene.h"
#include <map>

class SceneMgr : public IDebugable
{
public:
	void Init();
	void Shut();

	std::map<std::string, Scene> Scenes;
	Scene* ActiveScene;

	void AddNewScene(Scene& scene);
	void DeleteScene(std::string name);
	void SetActiveScene(std::string name);
	void AddTransformComponent(Entity& entity);
	void AddRenderComponent(Entity& entity);

	void AddSprite(Entity& entity);
	void AddStaticTile(Entity& entity);
	void SetTexture(Entity& entity, std::string txtName, std::string dataName);

	void DeleteScenes();

	virtual void DrawDebug() override;
};

