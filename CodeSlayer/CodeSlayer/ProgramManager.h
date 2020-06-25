//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 프로그램 관리자
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 프로그램 관리 및 흐름 제어

	2. 기능
		- 싱글톤 객체의 생성과 소멸
		- 시작 화면과 종료 화면 출력
		- 메인 루프 실행
		- 사용자 요청 기능 호출
*/

#pragma once
#include "Config.h"
#include "Console.h"
#include "MainMenu.h"
#include "WordPractice.h"
#include "ShortPractice.h"
#include "LongPractice.h"
#include "Statistics.h"
#include "MiniGame.h"


class ProgramManager
{
private:

	ProgramManager();
	~ProgramManager();

	/* 보조 클래스 */
	Console* mConsole;
	Keyboard* mKeyboard;
	Random* mRandom;

	/* 주 클래스 */
	MainMenu* mMainMenu;
	WordPractice* mWordPractice;
	ShortPractice* mShortPractice;
	LongPractice* mLongPractice;
	Statistics* mStatistics;
	MiniGame* mMiniGame;

	Screen mCurrentScreen;
	bool mQuit;

	const int mXPosTeamLogo = 36;
	const int mYPosTeamLogo = 6;
	const int mXPosTeamBoard = 41;
	const int mYPosTeamBoard = 17;
	const int mXPosTeamMember = 46;
	const int mYPosTeamMember = 19;
	const int mXPosProgramLogo = 11;
	const int mYPosProgramLogo = 31;

	const int mXPosTeamBoardBox = 42;
	const int mYPosTeamBoardBox = 18;
	const int mWidthTeamBoard = 45;
	const int mHeightTeamBoard = 5;

	const int mXPosPrompt = 53;
	const int mYPosPrompt = 20;

	/* 소개 화면 */
	void IntroScreen();

	/* 종료 화면 */
	void ExitScreen();

public:

	/* 프로그램 메인 루프 */
	void MainLoop();


private:
	static ProgramManager* sInstance;

public:
	static ProgramManager* Instance();
	static void Release();

};

