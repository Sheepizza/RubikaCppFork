#include "Globals.h"

#include <TextureMgr.h>
#include <SceneMgr.h>
#include <DebugMgr.h>
#include <Logger.h>
#include <InputMgr.h>

Globals gData;

Globals::Globals() : FrameCount(0)
{
	InputMgr = new ::InputMgr();
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
	InputMgr->Init();
	TextureMgr->Init();
	Logger->Init();
	SceneMgr->Init();
}

void Globals::Shut()
{
	InputMgr->Shut();
	TextureMgr->Shut();
	Logger->Shut();
	SceneMgr->Shut();
}

void Globals::Destroy()
{
	delete InputMgr;
	InputMgr = nullptr;

	delete TextureMgr;
	TextureMgr = nullptr;

	delete DebugMgr;
	DebugMgr = nullptr;

	delete Logger;
	Logger = nullptr;
}

void Globals::IncrementFrameCount()
{
	++FrameCount;
}

unsigned long long Globals::GetFrameCount()
{
	return FrameCount;
}

