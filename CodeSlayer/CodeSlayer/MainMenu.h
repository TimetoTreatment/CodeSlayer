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
#include "Mouse.h"

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
	Mouse* mMouse;

	GeneralMenu mSelectGeneralMenu;		// 현재 선택 중인 Phase 1 항목
	PracticeMenu mSelectPracticeMenu;	// 현재 선택 중인 Phase 2 항목

	Screen mNextScreen;					// 다음 기능
	bool mMoveScreen;					// 루프를 끝내야 한다면 True
	
	MainMenu();
	~MainMenu();


	const int mXPosTypingPracticeHitboxLT = 456;
	const int mYPosTypingPracticeHitboxLT = 415;
	const int mXPosTypingPracticeHitboxRB = 579;
	const int mYPosTypingPracticeHitboxRB = 433;

	const int mXPosMiniGameHitboxLT = 477;
	const int mYPosMiniGameHitboxLT = 477;
	const int mXPosMiniGameHitboxRB = 546;
	const int mYPosMiniGameHitboxRB = 495;

	const int mXPosExitHitboxLT = 492;
	const int mYPosExitHitboxLT = 543;
	const int mXPosExitHitboxRB = 530;
	const int mYPosExitHitboxRB = 561;

	const int mXPosWordHitboxLT = 444;
	const int mYPosWordHitboxLT = 427;
	const int mXPosWordHitboxRB = 481;
	const int mYPosWordHitboxRB = 445;

	const int mXPosShortHitboxLT = 496;
	const int mYPosShortHitboxLT = 427;
	const int mXPosShortHitboxRB = 536;
	const int mYPosShortHitboxRB = 445;

	const int mXPosLongHitboxLT = 549;
	const int mYPosLongHitboxLT = 427;
	const int mXPosLongHitboxRB = 584;
	const int mYPosLongHitboxRB = 445;

	const int mXPosStatisticsHitboxLT = 469;
	const int mYPosStatisticsHitboxLT = 510;
	const int mXPosStatisticsHitboxRB = 551;
	const int mYPosStatisticsHitboxRB = 529;

	const int mXPosBackHitboxLT = 495;
	const int mYPosBackHitboxLT = 559;
	const int mXPosBackHitboxRB = 531;
	const int mYPosBackHitboxRB = 577;

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