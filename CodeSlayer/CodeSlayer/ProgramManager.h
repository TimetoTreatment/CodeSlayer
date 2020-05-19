#pragma once
#include "Config.h"
#include "Random.h"
#include "MainMenu.h"
#include "Console.h"
#include <conio.h>
#include <fstream>

class ProgramManager
{
private:
	static ProgramManager* sInstance;

public:
	static ProgramManager* Instance();
	static void Release();

private:

	Console* mConsole;
	Random* mRandom;



	MainMenu* mMainMenu;



	Screen mCurrentScreen;






	bool mQuit;



public:

	ProgramManager();
	~ProgramManager();

	void MainLoop();
	void IntroScreen();
	void ExitScreen();


};

