#pragma once
#include "Console.h"
#include "Config.h"
#include <conio.h>
#include <fstream>

using namespace std;

class MainMenu
{
private:

	Console* mConsole;


	Screen mNextScreen;
	bool mQuit;


public:

	MainMenu();
	~MainMenu();


	void Main();
	Screen NextScreen();




};

