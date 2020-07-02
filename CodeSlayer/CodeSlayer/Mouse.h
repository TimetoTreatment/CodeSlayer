#pragma once
#include <Windows.h>
#include <iostream>
#include "Console.h"


using namespace std;


class Mouse
{

private:


	POINT mPoint;
	HWND hWnd;
	int mWindowSize = 0;
	RECT totalScore;




public:

	int keyPressed(int key)
	{
		return (GetAsyncKeyState(key) & (0x8000 != 0));
	}

	int main()
	{
		mPoint.x = 0;
		mPoint.y = 0;

		for (;;)
		{
			Console::Instance()->CursorPosition(0, 44);

			if (GetCursorPos(&mPoint)) {

				hWnd = WindowFromPoint(mPoint);
				ScreenToClient(hWnd, &mPoint);
				GetWindowRect(hWnd, &totalScore);
				mWindowSize = (totalScore.right - totalScore.left);

				cout << mPoint.x << "," << mPoint.y;
				
			}

			if (keyPressed(VK_LBUTTON))
				printf("%s\n", "ÁÂÅ¬¸¯");
		}

		Sleep(100);
	}

private:
	static Mouse* s_instance;

public:
	static Mouse* Instance();
	static void Release();
};

