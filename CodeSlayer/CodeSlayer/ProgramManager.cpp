#include "ProgramManager.h"

ProgramManager::ProgramManager()
{
	mConsole = Console::Instance();				// ���� Ŭ���� ��ü ����
	mRandom = Random::Instance();				//
	mKeyboard = Keyboard::Instance();			//
	mMouse = Mouse::Instance();					//
	mUserAnalysis = UserAnalysis::Instance();	//

	mMainMenu = MainMenu::Instance();			// �� Ŭ���� ��ü ����
	mWordPractice = WordPractice::Instance();	//
	mShortPractice = ShortPractice::Instance();	//
	mLongPractice = LongPractice::Instance();	//
	mStatistics = Statistics::Instance();		//
	mMiniGame = MiniGame::Instance();			//

	mCurrentScreen = Screen::MainMenu;			// ���� ȭ���� ���� �޴��� �ʱ�ȭ
	mQuit = false;
}


ProgramManager::~ProgramManager()
{
	mConsole->Release();		// ���� Ŭ���� ��ü �Ҹ�
	mRandom->Release();			//
	mKeyboard->Release();		//
	mMouse->Release();			//
	mUserAnalysis->Release();	//

	mMainMenu->Release();		// �� Ŭ���� ��ü �Ҹ�
	mWordPractice->Release();	//
	mShortPractice->Release();	//
	mLongPractice->Release();	//
	mStatistics->Release();		//
	mMiniGame->Release();		//
}


///////////////
/* �Ұ� ȭ�� */
///////////////
void ProgramManager::IntroScreen()
{
	Sleep(100);	// 1000
	mConsole->Draw("Assets/layout/intro_teamLogo.txt", "white", mXPosTeamLogo, mYPosTeamLogo);
	mConsole->Draw("Assets/layout/intro_teamBoard.txt", "white", mXPosTeamBoard, mYPosTeamBoard);
	mConsole->Draw("Assets/layout/intro_teamMember.txt", "white", mXPosTeamMember, mYPosTeamMember);
	Sleep(200);	// 2000
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", mXPosProgramLogo, mYPosProgramLogo);
	Sleep(200);	// 2000

	mConsole->Clear(mXPosTeamBoardBox, mYPosTeamBoardBox, mWidthTeamBoard, mHeightTeamBoard);

	for (;;)		// ������Ʈ ����
	{
		mConsole->Draw("* Press Enter to Start *", "white", mXPosPrompt, mYPosPrompt);	// ��� ������Ʈ
		Sleep(250);

		mKeyboard->DynamicInput();			// ���� �Է� (�ݺ����� ��� ����Ǿ�� �ϹǷ�, ���� �Է� X)
		if (mKeyboard->IsPressed("enter"))	// ���Ͱ� �ԷµǾ��ٸ�
			break;							// �ݺ��� ����

		mConsole->Draw("* Press Enter to Start *", "blue", mXPosPrompt, mYPosPrompt);	// �Ķ��� ������Ʈ
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear();		// ȭ�� �����
	mKeyboard->Clear();		// Ű���� �Է� �ʱ�ȭ (������Ʈ �������� �Է��� ���� ����)
}


///////////////
/* ���� ȭ�� */
///////////////
void ProgramManager::ExitScreen()
{
	mConsole->Draw("Assets/layout/intro_teamLogo.txt", "white", mXPosTeamLogo, mYPosTeamLogo);
	mConsole->Draw("Assets/layout/intro_teamBoard.txt", "white", mXPosTeamBoard, mYPosTeamBoard);
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", mXPosProgramLogo, mYPosProgramLogo);

	mConsole->Draw("Shutting Down CodeSlayer.", "white", mXPosPrompt - 1, mYPosPrompt);
	Sleep(500);

	mConsole->Draw("Shutting Down CodeSlayer..", "white", mXPosPrompt - 1, mYPosPrompt);
	Sleep(500);

	mConsole->Draw("Shutting Down CodeSlayer...", "white", mXPosPrompt - 1, mYPosPrompt);
	Sleep(500);

	mConsole->Draw("Shutting Down CodeSlayer...", "blue", mXPosPrompt - 1, mYPosPrompt);
	Sleep(1000);

	mConsole->CursorPosition(0, 40);
	mConsole->Color("default");
}


///////////////
/* ���� ���� */
///////////////
void ProgramManager::MainLoop()
{
	system("mode CON: COLS=130 LINES=45");	// �ܼ� ũ�� ���� (120, 30) -> (130, 45)
	IntroScreen();							// ���� ȭ�� ���

	for (; !mQuit;)
	{
		mMainMenu->Main();							// ���� �޴� Ŭ���� ����
		mCurrentScreen = mMainMenu->NextScreen();	// ����ڰ� ȣ���� ��� ������Ʈ

		switch (mCurrentScreen)		// ����ڰ� ȣ���� ���
		{
		case Screen::WordPractice:	// �ܾ��
			mWordPractice->Main();
			break;

		case Screen::ShortPractice:	// ª�� �� ����
			mShortPractice->Main();
			break;

		case Screen::LongPractice:	// �� �� ����
			mLongPractice->Main();
			break;

		case Screen::Statistics:	// ���
			mStatistics->Main();
			break;

		case Screen::MiniGame:		// �̴� ����
			mMiniGame->Main();
			break;

		case Screen::Exit:			// ����
			mQuit = true;
			break;
		}

		mConsole->Clear();		// ȭ�� ����
		mKeyboard->Clear();		// Ű���� �Է� �ʱ�ȭ
	}

	ExitScreen();	// ���� ȭ�� ���
}


ProgramManager* ProgramManager::sInstance = nullptr;

ProgramManager* ProgramManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new ProgramManager;

	return sInstance;
}

void ProgramManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
