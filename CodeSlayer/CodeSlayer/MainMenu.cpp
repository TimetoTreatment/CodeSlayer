#include "MainMenu.h"



MainMenu::MainMenu()
{
	mConsole = Console::Instance();

	mNextScreen = Screen::WordPractice;

	mQuit = 0;

}


MainMenu::~MainMenu()
{




}



void MainMenu::Main()
{
	int command;
	int x, y;
	char ch;
	fstream programLogo("Assets/intro_programLogo.txt", ios_base::in);
	fstream brickwall("Assets/mainmenu_brickwall.txt", ios_base::in);

	x = 10;
	y = 4;
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

	x = 8;
	y = 17;
	mConsole->Color("white");
	mConsole->CursorPosition(x, y);

	for (; !brickwall.eof();)
	{
		ch = brickwall.get();

		if (ch == '\n')
		{
			y++;
			mConsole->CursorPosition(x, y);
		}
		else
			cout << ch;
	}


	int xPosWordPractice = 58;
	int yPosWordPractice = 26;
	mConsole->Color("white");
	mConsole->CursorPosition(xPosWordPractice, yPosWordPractice);
	cout << "Word Practice";




	for (; !mQuit;)
	{
		switch (mNextScreen)
		{
		case Screen::WordPractice:
			mConsole->Color("red");
			mConsole->CursorPosition(xPosWordPractice, yPosWordPractice);
			cout << "Word Practice";
			break;

		case Screen::ShortPractice:


			break;

		case Screen::LongPractice:


			break;

		case Screen::MiniGame:


			break;

		case Screen::Exit:


			break;
		}

		if ((command = _getch()) == Key::arrow)
		{
			if ((command = _getch()) == Key::up)
			{
				mNextScreen--;

				if (mNextScreen == Screen::MainMenu)
					mNextScreen--;
			}

			else if (command == Key::down)
			{
				mNextScreen++;

				if (mNextScreen == Screen::MainMenu)
					mNextScreen++;
			}
		}

		else if (command == Key::enter)
			break;
	}









}

Screen MainMenu::NextScreen()
{
	return mNextScreen;
}