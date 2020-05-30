#pragma once
#include "Console.h"
#include "Config.h"
#include "Keyboard.h"

using namespace std;


class MainMenu
{
private:

	enum class GeneralMenu {

		TypingPractice,
		MiniGame,
		Exit,
	};
	friend void operator++(GeneralMenu& lhs, int);
	friend void operator--(GeneralMenu& lhs, int);

	enum class PracticeMenu {

		Word,
		Short,
		Long,
		Back,
	};
	friend void operator++(PracticeMenu& lhs, int);
	friend void operator--(PracticeMenu& lhs, int);

	Console* mConsole;
	Keyboard* mKeyboard;

	GeneralMenu mSelectGeneralMenu;
	PracticeMenu mSelectPracticeMenu;

	Screen mNextScreen;
	bool mMoveScreen;

	MainMenu();
	~MainMenu();

	const int mXPosMenuBox = 51;
	const int mYPosMenuBox = 23;
	const int mWidthMenuBox = 26;
	const int mHeightMenuBox = 14;

	const int mXPosTypingPractice = 57;
	const int mYPosTypingPractice = 26;
	const int mXPosMiniGame = 60;
	const int mYPosMiniGame = 30;
	const int mXPosExit = 62;
	const int mYPosExit = 34;

	const int mXPosWordPractice = 58;
	const int mYPosWordPractice = 25;
	const int mXPosShortPractice = 58;
	const int mYPosShortPractice = 28;
	const int mXPosLongPractice = 58;
	const int mYPosLongPractice = 31;
	const int mXPosBack = 62;
	const int mYPosBack = 35;

	/* 화면 출력 */
	void RenderLayout();
	void RenderGeneralMenu();
	void RenderPracticeMenu();

public:



	/* 메인 메뉴 루프 */
	void Main();

	Screen NextScreen();


private:
	static MainMenu* sInstance;

public:
	static MainMenu* Instance();
	static void Release();
};