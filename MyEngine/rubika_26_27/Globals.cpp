#include "Globals.h"

#include <TextureMgr.h>
#include <SceneMgr.h>
#include <DebugMgr.h>
#include <Logger.h>

Globals gData;

Globals::Globals() : FrameCount(0)
{
	TextureMgr = new ::TextureMgr();
	SceneMgr = new ::SceneMgr();
	DebugMgr = new ::DebugMgr();
	Logger = new ::Logger();
}

Globals::~Globals()
{
	Destroy();
}

void Globals::Init()
{
	TextureMgr->Init();
	Logger->Init();
	SceneMgr->Init();
}

void Globals::Shut()
{
	TextureMgr->Shut();
	Logger->Shut();
	SceneMgr->Shut();
}

void Globals::Destroy()
{
	delete DebugMgr;
	DebugMgr = nullptr;

	delete Logger;
	Logger = nullptr;
}

void Globals::IncrementFrameCount()
{
	++FrameCount;
}
