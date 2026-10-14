#pragma once

class TextureMgr;
class SceneMgr;
class DebugMgr;
class Logger;

class Globals
{
public:
	Globals();
	~Globals();

	void Init();
	void Shut();
	void Destroy();

	void IncrementFrameCount();

	unsigned long long FrameCount;

	TextureMgr* TextureMgr;
	SceneMgr* SceneMgr;
	DebugMgr* DebugMgr;
	Logger* Logger;
};

extern Globals gData;