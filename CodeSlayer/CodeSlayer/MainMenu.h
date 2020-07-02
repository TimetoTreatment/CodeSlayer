//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ���� �޴�
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- ���� �޴� ���
		- ����ڴ� ���� ���� ����� ����

	2. ���
		- ���α׷��� �����ϴ� ����� ���
		- ���� �޴��� �����ϰ�, ������� �Է��� ����
		- ����ڰ� ��û�� ����� ���α׷� �����ڷ� ��ȯ
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

	enum class GeneralMenu	// Phase 1 : �Ϲ� �޴�
	{
		TypingPractice,
		MiniGame,
		Exit,
	};
	friend void operator++(GeneralMenu& lhs, int);	// ���� �׸�
	friend void operator--(GeneralMenu& lhs, int);	// ���� �׸�

	enum class PracticeMenu // Phase 2 : Ÿ�� ���� �޴�
	{
		Word,
		Short,
		Long,
		Statistics,
		Back,
	};
	friend void operator++(PracticeMenu& lhs, int);	// ���� �׸�
	friend void operator--(PracticeMenu& lhs, int);	// ���� �׸�

	Console* mConsole;
	Keyboard* mKeyboard;
	Mouse* mMouse;

	GeneralMenu mSelectGeneralMenu;		// ���� ���� ���� Phase 1 �׸�
	PracticeMenu mSelectPracticeMenu;	// ���� ���� ���� Phase 2 �׸�

	Screen mNextScreen;					// ���� ���
	bool mMoveScreen;					// ������ ������ �Ѵٸ� True
	
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

	/* ȭ�� ��� */
	void RenderLayout();
	void RenderGeneralMenu();
	void RenderPracticeMenu();

public:

	/* ���� �޴� ���� */
	void Main();

	/* ����� ȣ�� ��� ��ȯ */
	Screen NextScreen();


private:
	static MainMenu* sInstance;

public:
	static MainMenu* Instance();
	static void Release();
};