#include "ProgramManager.h"

ProgramManager::ProgramManager()
{
	mConsole = Console::Instance();
	mRandom = Random::Instance();
	mKeyboard = Keyboard::Instance();

	mMainMenu = MainMenu::Instance();
	mWordPractice = WordPractice::Instance();
	mShortPractice = ShortPractice::Instance();
	mLongPractice = LongPractice::Instance();
	mStatistics = Statistics::Instance();
	mMiniGame = MiniGame::Instance();

	mCurrentScreen = Screen::MainMenu;
	mQuit = false;
}


ProgramManager::~ProgramManager()
{
	mConsole->Release();
	mRandom->Release();
	mKeyboard->Release();

	mMainMenu->Release();
	mWordPractice->Release();
	mShortPractice->Release();
	mLongPractice->Release();
	mStatistics->Release();
	mMiniGame->Release();
}


void ProgramManager::IntroScreen()
{
	Sleep(200);		// 1000
	mConsole->Draw("Assets/layout/intro_teamLogo.txt", "white", mXPosTeamLogo, mYPosTeamLogo);
	mConsole->Draw("Assets/layout/intro_teamBoard.txt", "white", mXPosTeamBoard, mYPosTeamBoard);
	mConsole->Draw("Assets/layout/intro_teamMember.txt", "white", mXPosTeamMember, mYPosTeamMember);
	Sleep(200);		// 1000
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", mXPosProgramLogo, mYPosProgramLogo);
	Sleep(200);		// 1000

	mConsole->Clear(mXPosTeamBoardBox, mYPosTeamBoardBox, mWidthTeamBoard, mHeightTeamBoard);

	for (;;)
	{
		mConsole->Draw("* Press Enter to Start *", "white", mXPosPrompt, mYPosPrompt);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;

		mConsole->Draw("* Press Enter to Start *", "blue", mXPosPrompt, mYPosPrompt);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


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


void ProgramManager::MainLoop()
{
	system("mode CON: COLS=130 LINES=45");
	IntroScreen();

	for (; !mQuit;)
	{
		mMainMenu->Main();
		mCurrentScreen = mMainMenu->NextScreen();

		switch (mCurrentScreen)
		{
		case Screen::WordPractice:
			mWordPractice->Main();
			mCurrentScreen = Screen::WordPractice;
			break;

		case Screen::ShortPractice:
			mShortPractice->Main();
			mCurrentScreen = Screen::ShortPractice;
			break;

		case Screen::LongPractice:
			mLongPractice->Main();
			mCurrentScreen = Screen::LongPractice;
			break;

		case Screen::MiniGame:
			mMiniGame->Main();
			mCurrentScreen = Screen::MainMenu;
			break;

		case Screen::Statistics:
			mStatistics->Main();
			mCurrentScreen = Screen::MainMenu;
			break;

		case Screen::Exit:
			mQuit = true;
			break;
		}

		mConsole->Clear();
		mKeyboard->Clear();
	}

	ExitScreen();
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
