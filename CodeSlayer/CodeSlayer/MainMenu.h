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

	/* ȭ�� ��� */
	void Render();

public:

	MainMenu();
	~MainMenu();

	/* ���� �޴� ���� */
	void Main();

	Screen NextScreen();
};