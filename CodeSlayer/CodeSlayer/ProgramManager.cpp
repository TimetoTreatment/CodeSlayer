#include "ProgramManager.h"

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


ProgramManager::ProgramManager()
{
	mConsole = Console::Instance();
	mRandom = Random::Instance();

	mMainMenu = new MainMenu;


	mCurrentScreen = Screen::MainMenu;
	mQuit = false;
}

ProgramManager::~ProgramManager()
{
	mConsole->Release();
	mRandom->Release();

	delete mMainMenu;
}


void ProgramManager::MainLoop()
{
	//Sleep(1000);
	IntroScreen();

	for (; !mQuit;)
	{
		switch (mCurrentScreen)
		{
		case Screen::MainMenu:
			mMainMenu->Main();

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
			ExitScreen();
			mQuit = true;
			break;
		}
	}
}


void ProgramManager::IntroScreen()
{
	int x, y;
	char ch;
	fstream teamLogo("Assets/intro_teamLogo.txt", ios_base::in);
	fstream teamBoard("Assets/intro_teamBoard.txt", ios_base::in);
	fstream teamMember("Assets/intro_teamMember.txt", ios_base::in);
	fstream programLogo("Assets/intro_programLogo.txt", ios_base::in);

	x = 36;
	y = 6;
	mConsole->Color("white");
	mConsole->CursorPosition(x, y);

	for (; !teamLogo.eof();)
	{
		ch = teamLogo.get();

		if (ch == '\n')
		{
			y++;
			mConsole->CursorPosition(x, y);
		}
		else
			cout << ch;
	}

	x = 41;
	y = 17;
	mConsole->Color("white");
	mConsole->CursorPosition(x, y);

	for (; !teamBoard.eof();)
	{
		ch = teamBoard.get();

		if (ch == '\n')
		{
			y++;
			mConsole->CursorPosition(x, y);
		}
		else
			cout << ch;
	}

	x = 46;
	y = 19;
	mConsole->CursorPosition(x, y);

	for (; !teamMember.eof();)
	{
		ch = teamMember.get();

		if (ch == '\n')
		{
			y++;
			mConsole->CursorPosition(x, y);
		}
		else
			cout << ch;
	}
	//Sleep(2000);

	x = 11;
	y = 31;
	mConsole->Color("blue");
	mConsole->CursorPosition(x, y);

	for (; !programLogo.eof();)
	{
		ch = programLogo.get();

		if (ch == '\n')
		{
			y++;
			mConsole->CursorPosition(x, y);
		}
		else
			cout << ch;
	}
	//Sleep(2000);

	for (y = 19; y < 22; y++)
	{
		mConsole->CursorPosition(46, y);

		for (x = 0; x < 40; x++)
			cout << ' ';
	}

	for (;;)
	{
		mConsole->CursorPosition(53, 20);
		mConsole->Color("white");
		cout << "* Press Enter to Start *";
		mConsole->CursorPosition(129, 44);
		Sleep(250);

		if (_kbhit() != 0 && _getch() == Key::enter)
			break;

		mConsole->CursorPosition(53, 20);
		mConsole->Color("blue");
		cout << "* Press Enter to Start *";
		mConsole->CursorPosition(129, 44);
		Sleep(250);

		if (_kbhit() != 0 && _getch() == Key::enter)
			break;
	}

	mConsole->Clear();

	teamLogo.close();
	teamBoard.close();
	teamMember.close();
	programLogo.close();
}


void ProgramManager::ExitScreen()
{




}