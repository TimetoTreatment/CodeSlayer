#pragma once
#include <Windows.h>
#include <iostream>
#include "Console.h"


using namespace std;


class Mouse
{

private:


	POINT mPointClick;
	POINT mPointScan;
	HWND hWnd;
	int mWindowSize = 0;
	RECT totalScore;


	int KeyPressed(int key)
	{
		return (GetAsyncKeyState(key) & (0x8000 != 0));
	}


public:


	void DynamicClick()
	{
		if (KeyPressed(VK_LBUTTON))
		{
			GetCursorPos(&mPointClick);

			hWnd = WindowFromPoint(mPointClick);
			ScreenToClient(hWnd, &mPointClick);
			GetWindowRect(hWnd, &totalScore);
			mWindowSize = (totalScore.right - totalScore.left);
		}
		else
		{
			mPointClick.x = 0;
			mPointClick.y = 0;
		}
	}

	int XPosClick() { return mPointClick.x; }
	int YPosClick() { return mPointClick.y; }

	void DynamicScan()
	{
		GetCursorPos(&mPointScan);

		hWnd = WindowFromPoint(mPointScan);
		ScreenToClient(hWnd, &mPointScan);
		GetWindowRect(hWnd, &totalScore);
		mWindowSize = (totalScore.right - totalScore.left);
	}

	int XPosScan() { return mPointScan.x; }
	int YPosScan() { return mPointScan.y; }

	void Clear()
	{
		mPointScan.x = 0;
		mPointScan.y = 0;
	}


private:
	static Mouse* s_instance;

public:
	static Mouse* Instance();
	static void Release();
};

