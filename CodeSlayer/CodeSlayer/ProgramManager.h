//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ���α׷� ������
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- ���α׷� ���� �� �帧 ����

	2. ���
		- �̱��� ��ü�� ������ �Ҹ�
		- ���� ȭ��� ���� ȭ�� ���
		- ���� ���� ����
		- ����� ��û ��� ȣ��
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

	/* ���� Ŭ���� */
	Console* mConsole;
	Keyboard* mKeyboard;
	Random* mRandom;

	/* �� Ŭ���� */
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

	/* �Ұ� ȭ�� */
	void IntroScreen();

	/* ���� ȭ�� */
	void ExitScreen();

public:

	/* ���α׷� ���� ���� */
	void MainLoop();


private:
	static ProgramManager* sInstance;

public:
	static ProgramManager* Instance();
	static void Release();

};

