#include "MainMenu.h"




enum class MainMenu::Menu {

	TypingPractice,
	MiniGame,
	Exit,
};


void operator++(MainMenu::Menu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::Menu::TypingPractice:
		lhs = MainMenu::Menu::MiniGame;
		break;

	case MainMenu::Menu::MiniGame:
		lhs = MainMenu::Menu::Exit;
		break;

	case MainMenu::Menu::Exit:
		lhs = MainMenu::Menu::TypingPractice;
		break;
	}
}


void operator--(MainMenu::Menu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::Menu::TypingPractice:
		lhs = MainMenu::Menu::Exit;
		break;

	case MainMenu::Menu::MiniGame:
		lhs = MainMenu::Menu::TypingPractice;
		break;

	case MainMenu::Menu::Exit:
		lhs = MainMenu::Menu::MiniGame;
		break;
	}
}


















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



void MainMenu::Render()
{
	const int xPosProgramLogo = 10;
	const int yPosProgramLogo = 5;
	const int xPosBrickwall = 6;
	const int yPosBrickwall = 17;
	const int xPosWordPractice = 57;
	const int yPosWordPractice = 26;
	const int xPosMiniGame = 60;
	const int yPosMiniGame = 30;
	const int xPosExit = 62;
	const int yPosExit = 34;
	int yMove;

	fstream programLogo("Assets/intro_programLogo.txt", ios_base::in);
	fstream brickwall("Assets/mainmenu_brickwall.txt", ios_base::in);
	string line;

	for (mConsole->Color("blue"), yMove = 0; !programLogo.eof(); yMove++)
	{
		getline(programLogo, line);

		mConsole->CursorPosition(xPosProgramLogo, yPosProgramLogo + yMove);
		cout << line;
	}

	for (mConsole->Color("white"), yMove = 0; !brickwall.eof(); yMove++)
	{
		getline(brickwall, line);

		mConsole->CursorPosition(xPosBrickwall, yPosBrickwall + yMove);
		cout << line;
	}

	for (; !mQuit;)
	{
		mConsole->Color("white");
		mConsole->CursorPosition(xPosWordPractice, yPosWordPractice);
		cout << "Typing Practice";
		mConsole->CursorPosition(xPosMiniGame, yPosMiniGame);
		cout << "MiniGame";
		mConsole->CursorPosition(xPosExit, yPosExit);
		cout << "Exit";

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

		if (mKeyboard->IsPressed("up"))
			mSelectMenu--;

		else if (mKeyboard->IsPressed("down"))
			mSelectMenu++;

		else if (mKeyboard->IsPressed("enter"))
			break;
	}
}


void MainMenu::Main()
{
	Render();

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



Screen MainMenu::NextScreen()
{
	return mNextScreen;
}