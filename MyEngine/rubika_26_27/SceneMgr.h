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
	void SetActiveScene(std::string name);

	void DeleteScenes();

	virtual void DrawDebug() override;
};

