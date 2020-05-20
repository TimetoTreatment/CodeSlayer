#pragma once
#include <fstream>
#include "Console.h"
#include "Config.h"
#include "Keyboard.h"

using namespace std;


class MainMenu
{
private:

	Console* mConsole;
	Keyboard* mKeyboard;

	enum class Menu
	{
		TypingPractice,
		MiniGame,
		Exit,

	};






	Menu mSelectMenu;

	Screen mNextScreen;
	bool mQuit;


public:

	MainMenu();
	~MainMenu();


	void Main();
	void Layout();
	Screen NextScreen();



	friend void operator++(Menu& lhs, int)
	{
		switch (lhs)
		{
		case Menu::TypingPractice:
			lhs = Menu::MiniGame;
			break;

		case Menu::MiniGame:
			lhs = Menu::Exit;
			break;

		case Menu::Exit:
			lhs = Menu::TypingPractice;
			break;
		}
	}


	friend void operator--(Menu& lhs, int)
	{
		switch (lhs)
		{
		case Menu::TypingPractice :
			lhs = Menu::Exit;
			break;

		case Menu::MiniGame:
			lhs = Menu::TypingPractice;
			break;

		case Menu::Exit:
			lhs = Menu::MiniGame;
			break;
		}
	}



};