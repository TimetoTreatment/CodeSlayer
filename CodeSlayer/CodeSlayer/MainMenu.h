//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 메인 메뉴
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 메인 메뉴 출력
		- 사용자는 다음 응용 기능을 선택

	2. 기능
		- 프로그램이 지원하는 기능을 출력
		- 메인 메뉴를 제공하고, 사용자의 입력을 받음
		- 사용자가 요청한 기능을 프로그램 관리자로 반환
*/

#pragma once
#include "Console.h"
#include "Config.h"
#include "Keyboard.h"

using namespace std;


class MainMenu
{
private:

	enum class GeneralMenu	// Phase 1 : 일반 메뉴
	{
		TypingPractice,
		MiniGame,
		Exit,
	};
	friend void operator++(GeneralMenu& lhs, int);	// 다음 항목
	friend void operator--(GeneralMenu& lhs, int);	// 이전 항목

	enum class PracticeMenu // Phase 2 : 타자 연습 메뉴
	{
		Word,
		Short,
		Long,
		Statistics,
		Back,
	};
	friend void operator++(PracticeMenu& lhs, int);	// 다음 항목
	friend void operator--(PracticeMenu& lhs, int);	// 이전 항목

	Console* mConsole;
	Keyboard* mKeyboard;

	GeneralMenu mSelectGeneralMenu;		// 현재 선택 중인 Phase 1 항목
	PracticeMenu mSelectPracticeMenu;	// 현재 선택 중인 Phase 2 항목

	Screen mNextScreen;					// 다음 기능
	bool mMoveScreen;					// 루프를 끝내야 한다면 True
	
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