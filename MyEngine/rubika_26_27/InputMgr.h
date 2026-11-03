#pragma once

#include <DebugMgr.h>
#include <InputAction.h>
#include <map>
#include <SFML/Graphics.hpp>

class InputMgr : public IDebugable
{
	public:
	void Init();
	void Shut();
	void CreateInputAction(const std::string& actionName);
	void DeleteInputAction(const std::string& actionName);

	void Update(float deltaTime);

	void RegisterCallback(const std::string& actionName, const std::string& debugName, std::function<void(float)> callback, void* owner);
	void UnregisterCallbacks(const std::string& actionName, void* owner);

	void BindAction(const std::string& actionName, sf::Keyboard::Key key);
	void UnbindAction(const std::string& actionName, sf::Keyboard::Key key);

	virtual void DrawDebug() override;

private:
	std::map<std::size_t, InputAction> InputActions;
	std::map<sf::Keyboard::Key, std::vector<std::size_t>> KeyBindings;

	void SetInputMapping(const std::string& path);
};

