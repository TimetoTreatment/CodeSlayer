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

	void dynamic()
	{
		mPoint.x = 0;
		mPoint.y = 0;

		if (keyPressed(VK_LBUTTON))
		{
			GetCursorPos(&mPoint);

			hWnd = WindowFromPoint(mPoint);
			ScreenToClient(hWnd, &mPoint);
			GetWindowRect(hWnd, &totalScore);
			mWindowSize = (totalScore.right - totalScore.left);
		}
		else
		{
			mPoint.x = 0;
			mPoint.y = 0;
		}
	}

	int GetX() { return mPoint.x; }
	int GetY() { return mPoint.y; }

private:
	static Mouse* s_instance;

public:
	static Mouse* Instance();
	static void Release();
};

