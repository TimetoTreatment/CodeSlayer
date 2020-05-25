#pragma once
#include "Config.h"
#include "Random.h"
#include "MainMenu.h"
#include "Console.h"
#include "TypingManager.h"

class ProgramManager
{
private:

	Console* mConsole;
	Keyboard* mKeyboard;
	Random* mRandom;
	TypingManager* TypingManager;
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

