#pragma once
#include "Config.h"
#include "Random.h"
#include "MainMenu.h"
#include "Console.h"
#include "WordPractice.h"
#include "ShortPractice.h"
#include "LongPractice.h"
#include "MiniGame.h"

class ProgramManager
{
private:

	Console* mConsole;
	Keyboard* mKeyboard;
	Random* mRandom;
	TypingManager* TypingManager;
	MainMenu* mMainMenu;

	WordPractice* mWordPractice;
	ShortPractice* mShortPractice;
	LongPractice* mLongPractice;
	MiniGame* mMiniGame;
	

	Screen mCurrentScreen;

	bool mQuit;

	/* 소개 화면 */
	void IntroScreen();

	/* 종료 화면 */
	void ExitScreen();


public:

	ProgramManager();
	~ProgramManager();

	/* 프로그램 메인 루프 */
	void MainLoop();


private:
	static ProgramManager* sInstance;

public:
	static ProgramManager* Instance();
	static void Release();

};

