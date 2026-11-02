#pragma once

#include <functional>
#include <string>
#include <vector>

class InputAction
{
public:
	InputAction() = default;
	InputAction(const std::string& name);
	void SetActionName(const std::string& name);
	void SetValue(float value);
	void RegisterCallback(const std::string& debugName, std::function<void(float)> callback, void* owner);
	void UnregisterCallbacks(void* owner);

	std::size_t GetActionNameHash();
	std::string GetActionName();
	float GetValue();

private:
	struct sCallbackInfo
	{
		std::string DebugName;
		std::function<void(float)> Callback;
		void* Owner = nullptr;
	};

	std::string ActionName;
	std::size_t ActionNameHash;
	float Value = 0.f;
	std::vector<sCallbackInfo> Callbacks;

	void InvokeCallbacks();
};