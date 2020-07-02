#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;


class Mouse
{
private:

	POINT mPointClick;
	POINT mPointScan;
	HWND hWnd;
	RECT totalScore;
	int mWindowSize = 0;

	int KeyPressed(int key);

public:

	void DynamicClick();

	int XPosClick() { return mPointClick.x; }
	int YPosClick() { return mPointClick.y; }

	void DynamicScan();

	int XPosScan() { return mPointScan.x; }
	int YPosScan() { return mPointScan.y; }

	void Clear();

private:
	static Mouse* s_instance;

public:
	static Mouse* Instance();
	static void Release();
};

