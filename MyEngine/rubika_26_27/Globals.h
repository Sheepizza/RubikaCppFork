#pragma once

class TextureMgr;
class SceneMgr;
class DebugMgr;
class Logger;
class InputMgr;

class Globals
{
public:
	Globals();
	~Globals();

	void Init();
	void Shut();
	void Destroy();

	void IncrementFrameCount();
	unsigned long long GetFrameCount();

	unsigned long long FrameCount;

	InputMgr* InputMgr;
	TextureMgr* TextureMgr;
	SceneMgr* SceneMgr;
	DebugMgr* DebugMgr;
	Logger* Logger;
};

extern Globals gData;