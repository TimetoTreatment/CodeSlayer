#pragma once
#include "Config.h"
#include "MainMenu.h"
#include "Console.h"
#include "WordPractice.h"
#include "ShortPractice.h"
#include "LongPractice.h"
#include "MiniGame.h"
#include "Statistics.h"


class ProgramManager
{
private:

	Console* mConsole;
	Keyboard* mKeyboard;
	Random* mRandom;

	MainMenu* mMainMenu;
	WordPractice* mWordPractice;
	ShortPractice* mShortPractice;
	LongPractice* mLongPractice;
	MiniGame* mMiniGame;
	Statistics* mStatistics;

	Screen mCurrentScreen;

	bool mQuit;

	/* �Ұ� ȭ�� */
	void IntroScreen();

	/* ���� ȭ�� */
	void ExitScreen();


public:

	ProgramManager();
	~ProgramManager();

	/* ���α׷� ���� ���� */
	void MainLoop();


private:
	static ProgramManager* sInstance;

public:
	static ProgramManager* Instance();
	static void Release();

};

