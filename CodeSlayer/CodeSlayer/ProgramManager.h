#pragma once
#include "Config.h"
#include "Random.h"
#include "MainMenu.h"
#include "Console.h"

class ProgramManager
{
private:

	Console* mConsole;
	Keyboard* mKeyboard;
	Random* mRandom;

	MainMenu* mMainMenu;

	Screen mCurrentScreen;

	bool mQuit;

	void IntroScreen();
	void ExitScreen();

public:

	ProgramManager();
	~ProgramManager();

	void MainLoop();

private:
	static ProgramManager* sInstance;

public:
	static ProgramManager* Instance();
	static void Release();

};

