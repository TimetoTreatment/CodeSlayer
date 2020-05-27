#pragma once
#include "Console.h"
#include "Config.h"
#include "Keyboard.h"

using namespace std;


class MainMenu
{
private:

	enum class Menu;
	friend void operator++(Menu& lhs, int);
	friend void operator--(Menu& lhs, int);

	Console* mConsole;
	Keyboard* mKeyboard;

	Menu mSelectMenu;

	Screen mNextScreen;

	/* 화면 출력 */
	void Render();

public:

	MainMenu();
	~MainMenu();

	/* 메인 메뉴 루프 */
	void Main();

	Screen NextScreen();
};