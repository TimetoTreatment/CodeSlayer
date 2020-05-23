#include "ProgramManager.h"



ProgramManager::ProgramManager()
{
	mConsole = Console::Instance();
	mRandom = Random::Instance();
	mKeyboard = Keyboard::Instance();

	mMainMenu = new MainMenu;

	mCurrentScreen = Screen::MainMenu;
	mQuit = false;
}

ProgramManager::~ProgramManager()
{
	mConsole->Release();
	mRandom->Release();
	mKeyboard->Release();

	delete mMainMenu;
}



void ProgramManager::IntroScreen()
{
	// Sleep(1000);
	mConsole->Draw("Assets/intro_teamLogo.txt", "white", 36, 6);
	mConsole->Draw("Assets/intro_teamBoard.txt", "white", 41, 17);
	mConsole->Draw("Assets/intro_teamMember.txt", "white", 46, 19);
	// Sleep(3000);
	mConsole->Draw("Assets/intro_programLogo.txt", "blue", 11, 31);
	// Sleep(3000);

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

}







void ProgramManager::MainLoop()
{
	system("mode CON: COLS=130 LINES=45");
	IntroScreen();

	for (; !mQuit;)
	{
		switch (mCurrentScreen)
		{
		case Screen::MainMenu:
			mMainMenu->Main();
			mCurrentScreen = mMainMenu->NextScreen();
			break;

		case Screen::WordPractice:


			break;

		case Screen::ShortPractice:


			break;

		case Screen::LongPractice:


			break;

		case Screen::MiniGame:


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
