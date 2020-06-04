#include "ProgramManager.h"

ProgramManager::ProgramManager()
{
	mConsole = Console::Instance();
	mRandom = Random::Instance();
	mKeyboard = Keyboard::Instance();
	TypingManager = TypingManager::Instance();

	mMainMenu = MainMenu::Instance();
	mWordPractice = WordPractice::Instance();
	mShortPractice = ShortPractice::Instance();
	mLongPractice = LongPractice::Instance();

	mMiniGame = new MiniGame;

	mCurrentScreen = Screen::MainMenu;
	mQuit = false;
}


ProgramManager::~ProgramManager()
{
	mConsole->Release();
	mRandom->Release();
	mKeyboard->Release();
	TypingManager->Release();

	mMainMenu->Release();
	mWordPractice->Release();
	mShortPractice->Release();
	mLongPractice->Release();
}


void ProgramManager::IntroScreen()
{
	Sleep(100);	// 100 * 10
	mConsole->Draw("Assets/layout/intro_teamLogo.txt", "white", 36, 6);
	mConsole->Draw("Assets/layout/intro_teamBoard.txt", "white", 41, 17);
	mConsole->Draw("Assets/layout/intro_teamMember.txt", "white", 46, 19);
	Sleep(300);	// 100 * 10
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", 11, 31);
	Sleep(300);	// 300 * 10

	mConsole->Clear(46, 19, 40, 3);

	for (;;)
	{
		mConsole->Draw("* Press Enter to Start *", "white", 53, 20);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;

		mConsole->Draw("* Press Enter to Start *", "blue", 53, 20);
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
	mConsole->Color("default");
}


void ProgramManager::MainLoop()
{
	system("mode CON: COLS=130 LINES=45");
	IntroScreen();

	for (; !mQuit;)
	{
		mCurrentScreen = Screen::MainMenu;
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

		case Screen::Exit:
			mQuit = true;
			break;
		}
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
