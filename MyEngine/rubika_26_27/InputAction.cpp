#include "InputAction.h"
#include "Logger.h"
#include <format>

InputAction::InputAction(const std::string& name) : ActionName(name), ActionNameHash(std::hash<std::string>{}(name))
{
}

void InputAction::SetActionName(const std::string& name)
{
	ActionName = name;
}

void InputAction::SetValue(float value)
{
	//Logger::Info(std::format("Action {} invoked.", ActionName));

	Value = value;

	if (Value != 0.f)
	{
		InvokeCallbacks();
	}
}

void InputAction::RegisterCallback(const std::string& debugName, std::function<void(float)> callback, void* owner)
{
	Callbacks.push_back({ debugName, callback, owner });
}

void InputAction::UnregisterCallbacks(void* owner)
{
	for (size_t i = Callbacks.size() - 1; i >= 0; i--)
	{
		if (Callbacks[i].Owner == owner)
		{
			Callbacks.erase(Callbacks.begin() + i);
		}
	}
}

std::size_t InputAction::GetActionNameHash()
{
	return ActionNameHash;
}

std::string InputAction::GetActionName()
{
	return ActionName;
}

float InputAction::GetValue()
{
	return Value;
}

void InputAction::InvokeCallbacks()
{
	for (sCallbackInfo callback : Callbacks)
	{
		callback.Callback(Value);
	}
}
