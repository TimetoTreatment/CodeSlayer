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
		Statistics,
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

	const int mXPosPracticeBox = 53;
	const int mYPosPracticeBox = 25;

	const int mXPosWordPractice = 56;
	const int mYPosWordPractice = 27;
	const int mXPosShortPractice = 62;
	const int mYPosShortPractice = 27;
	const int mXPosLongPractice = 69;
	const int mYPosLongPractice = 27;
	const int mXPosStatisticsPractice = 59;
	const int mYPosStatisticsPractice = 32;
	const int mXPosBack = 62;
	const int mYPosBack = 35;

	/* 화면 출력 */
	void RenderLayout();
	void RenderGeneralMenu();
	void RenderPracticeMenu();

public:

	/* 메인 메뉴 루프 */
	void Main();

	/* 사용자 호출 기능 반환 */
	Screen NextScreen();


private:
	static MainMenu* sInstance;

public:
	static MainMenu* Instance();
	static void Release();
};