#include "MainMenu.h"



MainMenu::MainMenu()
{
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();

	mNextScreen = Screen::WordPractice;
	mSelectMenu = Menu::TypingPractice;

	mQuit = 0;

}


MainMenu::~MainMenu()
{




}



void MainMenu::Main()
{
	int x, y;
	char ch;
	fstream programLogo("Assets/intro_programLogo.txt", ios_base::in);
	fstream brickwall("Assets/mainmenu_brickwall.txt", ios_base::in);

	x = 10;
	y = 5;
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

	x = 6;
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

	int xPosWordPractice = 57;
	int yPosWordPractice = 26;
	mConsole->Color("white");
	mConsole->CursorPosition(xPosWordPractice, yPosWordPractice);
	cout << "Typing Practice";

	int xPosMiniGame = 60;
	int yPosMiniGame = 30;
	mConsole->Color("white");
	mConsole->CursorPosition(xPosMiniGame, yPosMiniGame);
	cout << "MiniGame";

	int xPosExit = 62;
	int yPosExit = 34;
	mConsole->Color("white");
	mConsole->CursorPosition(xPosExit, yPosExit);
	cout << "Exit";

	for (; !mQuit;)
	{
		switch (mSelectMenu)
		{
		case Menu::TypingPractice:
			mConsole->Color("red");
			mConsole->CursorPosition(xPosWordPractice, yPosWordPractice);
			cout << "Typing Practice";

			break;

		case Menu::MiniGame:
			mConsole->Color("green");
			mConsole->CursorPosition(xPosMiniGame, yPosMiniGame);
			cout << "MiniGame";

			break;

		case Menu::Exit:
			mConsole->Color("blue");
			mConsole->CursorPosition(xPosExit, yPosExit);
			cout << "Exit";

			break;
		}

		mKeyboard->StaticInput();

		mConsole->Color("white");
		mConsole->CursorPosition(xPosWordPractice, yPosWordPractice);
		cout << "Typing Practice";

		mConsole->CursorPosition(xPosMiniGame, yPosMiniGame);
		cout << "MiniGame";

		mConsole->CursorPosition(xPosExit, yPosExit);
		cout << "Exit";

		if (mKeyboard->IsPressed("up"))
			mSelectMenu--;

		else if (mKeyboard->IsPressed("down"))
			mSelectMenu++;

		else if (mKeyboard->IsPressed("enter"))
			break;
	}

	switch (mSelectMenu)
	{
	case Menu::TypingPractice:


		break;

	case Menu::MiniGame:


		break;

	case Menu::Exit:
		mNextScreen = Screen::Exit;

		break;
	}

	mKeyboard->Clear();
	mConsole->Clear();
}


void Layout()
{
	int asdf=1;
	asdf++;
}



Screen MainMenu::NextScreen()
{
	return mNextScreen;
}