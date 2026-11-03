#include "SceneMgr.h"
#include "Logger.h"
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <DynamicColliderComponent.h>
#include <Rectangle.h>
#include <Sprite.h>
#include <Globals.h>

#include <format>

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

void SceneMgr::Init()
{
	gData.DebugMgr->RegisterDebugableWindow("SceneManager", this);
}

void SceneMgr::Shut()
{
	gData.DebugMgr->UnregisterDebugableWindow("SceneManager");
}

void SceneMgr::Update(float fDeltaTime)
{
	if (ActiveScene != nullptr)
	{
		ActiveScene->Update(fDeltaTime);
	}
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	if (ActiveScene != nullptr)
	{
		ActiveScene->Draw(window);
	}
}

void SceneMgr::DrawDebug()
{
#ifdef _USE_IMGUI

	int id = 0;

	ImGui::PushID(id);

	static char str[32] = "";
	ImGui::SetNextItemWidth(200.0f);
	ImGui::InputText("##SceneName", str, sizeof(str));

	ImGui::SameLine();

	if (ImGui::Button("Add Scene"))
	{
		Scene newScene = Scene(str);
		gData.SceneMgr->AddNewScene(newScene);
	}

	ImGui::PopID();

	id++;

	for (auto& kv : Scenes)
	{
		id++;

		Scene* scene = &kv.second;

		ImGui::PushID(id);

		if (ImGui::BeginTable("Scenes", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
		{
			ImGui::TableSetupColumn("Scene");
			ImGui::TableSetupColumn("IsActive");
			ImGui::TableSetupColumn("Actions");
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();

			static int clicked = 0;

			const char* isActive = scene == ActiveScene ? "true" : "false";

			ImGui::TableSetColumnIndex(0);
			ImGui::Text(scene->Name.c_str());
			ImGui::SetItemTooltip(scene->GetEntities().c_str());
			ImGui::TableSetColumnIndex(1);
			ImGui::Text(isActive);
			ImGui::TableSetColumnIndex(2);

			if (ImGui::Button("Set Active"))
				SetActiveScene(scene->Name);

			ImGui::SameLine();

			if (ImGui::Button("Delete"))
				DeleteScene(scene->Name);

			static char eStr[32] = "";
			ImGui::SetNextItemWidth(200.0f);
			ImGui::InputText("##EntityName", eStr, sizeof(eStr));

			ImGui::SameLine();

			if (ImGui::Button("Add Entity"))
				scene->CreateEntity(eStr);

			ImGui::EndTable();
		}

		ImGui::PopID();

		id++;

		if (ImGui::BeginTable("Entities", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
		{
			ImGui::TableSetupColumn("Entity");
			ImGui::TableSetupColumn("Actions");
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();

			for (auto entity : scene->Entities)
			{
				ImGui::PushID(id);

				ImGui::TableNextColumn();
				ImGui::Text(entity->Name.c_str());
				ImGui::TableNextColumn();

				DynamicColliderComponent* coll = entity->GetComponent<DynamicColliderComponent>();

				if (coll == nullptr)
				{
					if (ImGui::Button("Add Collider"))
						entity->AddComponent<DynamicColliderComponent>();
				}
				else
				{
					static float size[2] = { 1.f, 1.f };
					ImGui::InputFloat2("size", size);

					ImGui::SameLine();

					if (ImGui::Button("Set Size"))
						coll->SetHitboxSize({ size[0], size[1] });

					static float offset[2] = { 0.f, 0.f };
					ImGui::InputFloat2("offset", offset);

					ImGui::SameLine();

					if (ImGui::Button("Set Offset"))
						coll->SetHitboxOffset({ offset[0], offset[1] });
				}

				/*if (ImGui::Button("Add Transform"))
					AddTransformComponent(*entity);

				RenderComponent* r = entity->GetComponent<RenderComponent>();

				if (r == nullptr)
				{
					if (ImGui::Button("Add Render"))
						AddRenderComponent(*entity);
				}
				else
				{
					if (r->GetDrawable<Sprite>() == nullptr)
					{
						if (ImGui::Button("Add Sprite"))
							AddSprite(*entity);
					}
					else
					{
						static char txtStr[32] = "";
						ImGui::SetNextItemWidth(150.f);
						ImGui::InputText("##TextureName", txtStr, sizeof(txtStr));

						ImGui::SameLine();

						static char spriteStr[32] = "";
						ImGui::SetNextItemWidth(150.f);
						ImGui::InputText("##TileName", spriteStr, sizeof(spriteStr));

						ImGui::SameLine();

						if (ImGui::Button("Set Texture"))
							SetTexture(*entity, txtStr, spriteStr);
					}

					if (r->GetDrawable<StaticTile>() == nullptr)
					{
						if (ImGui::Button("Add Static Tile"))
							AddStaticTile(*entity);
					}
					else
					{
						static char txtStr[32] = "";
						ImGui::SetNextItemWidth(150.f);
						ImGui::InputText("##TextureName", txtStr, sizeof(txtStr));

						ImGui::SameLine();

						static char tileStr[32] = "";
						ImGui::SetNextItemWidth(150.f);
						ImGui::InputText("##TileName", tileStr, sizeof(tileStr));

						ImGui::SameLine();

						if (ImGui::Button("Set Texture"))
							SetTexture(*entity, txtStr, tileStr);
					}
				}*/

				ImGui::TableNextRow();

				id++;

				ImGui::PopID();
			}

			ImGui::EndTable();
		}
	}
#endif
}

void SceneMgr::DisplayColliders(bool enable)
{
	if (ActiveScene != nullptr)
	{
		for (Entity* entity : ActiveScene->Entities)
		{
			DynamicColliderComponent* coll = entity->GetComponent<DynamicColliderComponent>();
			if (coll != nullptr)
			{
				coll->DisplayColliders(enable);
			}
		}
	}
}

void SceneMgr::AddNewScene(Scene& scene)
{
	if (scene.Name == "")
	{
		Logger::Warning("Scene's name can't be null.");
		return;
	}

	if (Scenes.contains(scene.Name))
	{
		Logger::Warning(std::format("The name {} is already used.", scene.Name));
		return;
	}

	Scenes.emplace(scene.Name, scene);
}

void SceneMgr::DeleteScene(std::string name)
{
	if (!Scenes.contains(name))
	{
		Logger::Warning(std::format("Scene Manager doesn't contains {}.", name));
		return;
	}

	if (ActiveScene->Name == name)
	{
		Logger::Warning(std::format("Can't delete the active scene.", name));
		return;
	}

	Scene* scene = &Scenes.at(name);
	scene->Destroy();
	//Scenes.erase(name);
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

void SceneMgr::AddTransformComponent(Entity& entity)
{
	entity.AddComponent<TransformComponent>();
}

void SceneMgr::AddRenderComponent(Entity& entity)
{
	entity.AddComponent<RenderComponent>();
}

void SceneMgr::AddSprite(Entity& entity)
{
	RenderComponent* r = entity.GetComponent<RenderComponent>();

	if (r == nullptr)
	{
		Logger::Warning(std::format("Can't add sprite to {}, there's no Render Component attached.", entity.Name));
		return;
	}

	r->AddDrawable<Sprite>(0,0);
}

void SceneMgr::AddStaticTile(Entity& entity)
{
	RenderComponent* r = entity.GetComponent<RenderComponent>();

	if (r == nullptr)
	{
		Logger::Warning(std::format("Can't add static tile to {}, there's no Render Component attached.", entity.Name));
		return;
	}

	r->AddDrawable<StaticTile>(0,0);
}

void SceneMgr::SetTexture(Entity& entity, std::string txtName, std::string dataName)
{
	RenderComponent* r = entity.GetComponent<RenderComponent>();

	if (r == nullptr)
	{
		Logger::Warning(std::format("There is no Render Component in {}.", entity.Name));
		return;
	}

	StaticTile* tile = r->GetDrawable<StaticTile>();

	if (tile != nullptr)
	{
		if (!tile->SetTextureAndStaticTile(txtName, dataName))
		{
			Logger::Warning(std::format("Texture {} or Tile {} doesn't exist.", txtName, dataName));
		}
		return;
	}

	Sprite* sprite = r->GetDrawable<Sprite>();

	if (sprite != nullptr)
	{
		if (!sprite->SetTextureAndSprite(txtName, dataName))
		{
			Logger::Warning(std::format("Texture {} or Sprite {} doesn't exist.", txtName, dataName));
		}
		return;
	}

	Logger::Warning(std::format("There is no Drawable in {}.", entity.Name));
	return;
}

void SceneMgr::DeleteScenes()
{
	ActiveScene->Destroy();

	Scenes.clear();
}
