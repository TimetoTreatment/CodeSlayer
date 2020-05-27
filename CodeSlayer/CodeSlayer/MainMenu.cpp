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
	case MainMenu::Menu::TypingPractice:	lhs = MainMenu::Menu::MiniGame;			break;
	case MainMenu::Menu::MiniGame:			lhs = MainMenu::Menu::Exit;				break;
	case MainMenu::Menu::Exit:				lhs = MainMenu::Menu::TypingPractice;	break;
	}
}

void operator--(MainMenu::Menu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::Menu::TypingPractice:	lhs = MainMenu::Menu::Exit;				break;
	case MainMenu::Menu::MiniGame:			lhs = MainMenu::Menu::TypingPractice;	break;
	case MainMenu::Menu::Exit:				lhs = MainMenu::Menu::MiniGame;			break;
	}
}


MainMenu::MainMenu()
{
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();

	mNextScreen = Screen::WordPractice;

	mSelectMenu = Menu::TypingPractice;
}


MainMenu::~MainMenu()
{

}


void MainMenu::Render()
{
	const int xPosWordPractice = 57;
	const int yPosWordPractice = 26;
	const int xPosMiniGame = 60;
	const int yPosMiniGame = 30;
	const int xPosExit = 62;
	const int yPosExit = 34;

	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", 10, 5);
	mConsole->Draw("Assets/layout/mainmenu_brickwall.txt", "white", 6, 17);

	for (;;)
	{
		mConsole->Draw("Typing Practice", "white", xPosWordPractice, yPosWordPractice);
		mConsole->Draw("MiniGame", "white", xPosMiniGame, yPosMiniGame);
		mConsole->Draw("Exit", "white", xPosExit, yPosExit);

		switch (mSelectMenu)
		{
		case Menu::TypingPractice:
			mConsole->Draw("Typing Practice", "red", xPosWordPractice, yPosWordPractice);

			break;

		case Menu::MiniGame:
			mConsole->Draw("MiniGame", "green", xPosMiniGame, yPosMiniGame);

			break;

		case Menu::Exit:
			mConsole->Draw("Exit", "blue", xPosExit, yPosExit);

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
		mNextScreen = Screen::MiniGame;

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


MainMenu* MainMenu::sInstance = nullptr;

MainMenu* MainMenu::Instance()
{
	if (sInstance == nullptr)
		sInstance = new MainMenu;

	return sInstance;
}

void MainMenu::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
