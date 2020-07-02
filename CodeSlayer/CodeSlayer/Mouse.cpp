#include "Mouse.h"


int Mouse::KeyPressed(int key)
{
	return (GetAsyncKeyState(key) & (0x8000 != 0));
}


void Mouse::DynamicClick()
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


void Mouse::DynamicScan()
{
	GetCursorPos(&mPointScan);

	hWnd = WindowFromPoint(mPointScan);
	ScreenToClient(hWnd, &mPointScan);
	GetWindowRect(hWnd, &totalScore);
	mWindowSize = (totalScore.right - totalScore.left);
}


void Mouse::Clear()
{
	mPointScan.x = 0;
	mPointScan.y = 0;
}


Mouse* Mouse::s_instance = nullptr;

Mouse* Mouse::Instance()
{
	if (s_instance == nullptr)
		s_instance = new Mouse;

	return s_instance;
}

void Mouse::Release()
{
	delete s_instance;
	s_instance = nullptr;
}