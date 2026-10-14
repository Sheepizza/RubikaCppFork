#include "SceneMgr.h"
#include "Logger.h"

#include <format>

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#include <Globals.h>
#endif

void SceneMgr::Init()
{
	gData.DebugMgr->RegisterDebugableWindow("SceneManager", this);
}

void SceneMgr::Shut()
{
	gData.DebugMgr->UnregisterDebugableWindow("SceneManager");
}

void SceneMgr::DrawDebug()
{
#ifdef _USE_IMGUI
	if (ImGui::BeginTable("Logs##LogConsole", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
	{
		ImGui::TableSetupColumn("Scene");
		ImGui::TableSetupColumn("IsActive");
		ImGui::TableSetupColumn("Actions");
		ImGui::TableHeadersRow();
		ImGui::TableNextRow();

		int id = 0;

		for (auto& kv : Scenes)
		{
			id++;
			static int clicked = 0;

			Scene* scene = &kv.second;

			const char* isActive = scene == ActiveScene ? "true" : "false";


			ImGui::TableSetColumnIndex(0);
			ImGui::Text(scene->Name.c_str());
			ImGui::SetItemTooltip(scene->GetEntities().c_str());
			ImGui::TableSetColumnIndex(1);
			ImGui::Text(isActive);
			ImGui::TableSetColumnIndex(2);

			ImGui::PushID(id);
			if (ImGui::Button("Set Active"))
				SetActiveScene(scene->Name);
			ImGui::PopID();

			id++;

			ImGui::PushID(id);
			if (ImGui::Button("Add Entity"))
				scene->CreateEntity();
			ImGui::PopID();

			ImGui::TableNextRow();
		}

		ImGui::EndTable();
	}
#endif
}

void SceneMgr::AddNewScene(Scene& scene)
{
	if (Scenes.contains(scene.Name))
	{
		Logger::Warning(std::format("The name {} is already used.", scene.Name));
		return;
	}

	Scenes.emplace(scene.Name, scene);
}

void SceneMgr::SetActiveScene(std::string name)
{
	if (!Scenes.contains(name))
	{
		Logger::Warning(std::format("Scene Manager doesn't contains {}.", name));
		return;
	}

	ActiveScene = &Scenes.at(name);
	ActiveScene->Start();
}

void SceneMgr::DeleteScenes()
{
	ActiveScene->Destroy();

	Scenes.clear();
}
