#include "InputMgr.h"
#include <Globals.h>
#include <format>
#include <Logger.h>
#include <fstream>

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

void InputMgr::Init()
{
	gData.DebugMgr->RegisterDebugableWindow("InputManager", this);
	SetInputMapping("../Ressources/InputMapping.csv");
}

void InputMgr::Shut()
{
	gData.DebugMgr->UnregisterDebugableWindow("InputManager");
}

void InputMgr::Update(float deltaTime)
{
	for(const auto& kv: KeyBindings)
	{
		if (sf::Keyboard::isKeyPressed(kv.first))
		{
			for (size_t name : kv.second)
			{
				InputActions[name].SetValue(1.f);
			}
		}

		else
		{
			for (size_t name : kv.second)
			{
				InputActions[name].SetValue(0.f);
			}
		}
	}
}

void InputMgr::CreateInputAction(const std::string& actionName)
{
	std::size_t hashedName = std::hash<std::string>{}(actionName);

	if (InputActions.find(hashedName) != InputActions.end())
	{
		Logger::Warning(std::format("Input action {} already registered.", actionName));
		return;
	}

	//Logger::Info(std::format("Input action {} registered.", actionName));
	InputActions.emplace(hashedName, InputAction(actionName));
}

void InputMgr::DeleteInputAction(const std::string& actionName)
{
	//Logger::Info(std::format("Input Actions cleared.", actionName));

	InputActions.clear();
}

void InputMgr::RegisterCallback(const std::string& actionName, const std::string& debugName, std::function<void(float)> callback, void* owner)
{
	std::size_t hashedName = std::hash<std::string>{}(actionName);
	
	if (InputActions.find(hashedName) == InputActions.end())
	{
		Logger::Warning(std::format("Input action {} not found.", actionName));
		return;
	}

	InputActions[hashedName].RegisterCallback(debugName, callback, owner);
}

void InputMgr::UnregisterCallbacks(const std::string& actionName, void* owner)
{
	std::size_t hashedName = std::hash<std::string>{}(actionName);

	if (InputActions.find(hashedName) == InputActions.end())
	{
		Logger::Warning(std::format("Input action {} not found.", actionName));
		return;
	}

	InputActions[hashedName].UnregisterCallbacks(owner);
}

void InputMgr::BindAction(const std::string& actionName, sf::Keyboard::Key key)
{
	std::size_t hashedName = std::hash<std::string>{}(actionName);

	if (InputActions.find(hashedName) == InputActions.end())
	{
		Logger::Warning(std::format("Input action {} not found.", actionName));
		return;
	}

	KeyBindings[key].push_back(hashedName);
}

void InputMgr::UnbindAction(const std::string& actionName, sf::Keyboard::Key key)
{
	std::size_t hashedName = std::hash<std::string>{}(actionName);

	if (InputActions.find(hashedName) == InputActions.end())
	{
		Logger::Warning(std::format("Input action {} not found.", actionName));
		return;
	}

	for (size_t i = 0; i < KeyBindings[key].size(); i++)
	{
		if (KeyBindings[key][i] == hashedName)
		{
			KeyBindings[key].erase(KeyBindings[key].begin() + i);
			return;
		}
	}

	Logger::Warning(std::format("Input action {} isn't bind.", actionName));
}

void InputMgr::DrawDebug()
{
#ifdef _USE_IMGUI

	int id = 0;

	ImGui::PushID(id);

	if (ImGui::BeginTable("Actions", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
	{
		ImGui::TableSetupColumn("InputAction");
		ImGui::TableSetupColumn("Value");
		ImGui::TableHeadersRow();
		ImGui::TableNextRow();

		for (auto& kv : InputActions)
		{
			ImGui::PushID(id);

			ImGui::TableNextColumn();
			ImGui::Text(kv.second.GetActionName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(std::to_string(kv.second.GetValue()).c_str());
			ImGui::PopID();
		}
		ImGui::EndTable();
	}

	ImGui::PopID();

	ImGui::PushID(id);

	if (ImGui::BeginTable("Bindings", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
	{
		ImGui::TableSetupColumn("Key");
		ImGui::TableSetupColumn("InputAction");
		ImGui::TableSetupColumn("Actions");
		ImGui::TableHeadersRow();
		ImGui::TableNextRow();

		for (auto& kv : KeyBindings)
		{
			id++;

			ImGui::PushID(id);
			ImGui::TableNextColumn();
			ImGui::Text("%c", static_cast<char>((int)kv.first + 65));
			ImGui::TableNextColumn();
			for (size_t name : kv.second)
			{
				id++;
				ImGui::PushID(id);
				ImGui::Text(InputActions[name].GetActionName().c_str());
				ImGui::SameLine();
				if (ImGui::Button("Unbind Action"))
					UnbindAction(InputActions[name].GetActionName(), kv.first);
				ImGui::PopID();
			}
			ImGui::TableNextColumn();

			const char* actions[] = { "Up", "Down", "Left", "Right"};
			static int index = 0;
			ImGui::SetNextItemWidth(100.0f);
			ImGui::Combo("Combo", &index, actions, IM_ARRAYSIZE(actions));
			ImGui::SameLine();

			if (ImGui::Button("Bind Action"))
				BindAction(actions[index], kv.first);

			ImGui::PopID();
		}
		ImGui::EndTable();
	}

	ImGui::PopID();

	id++;
#endif
}

void InputMgr::SetInputMapping(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		Logger::Warning("Failed to open Input Mapping.");
		return;
	}

	std::string line;
	std::string cell;

	std::getline(file, line);

	std::stringstream lineStream(line);

	while (std::getline(lineStream, cell, ','))
	{
		CreateInputAction(cell);
	}

	while (std::getline(file, line))
	{
		std::stringstream lineStream(line);

		std::getline(lineStream, cell, ',');

		std::getline(lineStream, cell, ',');
		
		sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(std::stoi(cell));

		while (std::getline(lineStream, cell, ','))
		{
			gData.InputMgr->BindAction(cell, key);
		}
	}
	file.close();
}
