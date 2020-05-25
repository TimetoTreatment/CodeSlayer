#include "Keyboard.h"

Keyboard::Keyboard()
{
	mLastKey = 0;
}


void Keyboard::StaticInput()
{
	mLastKey = _getch();

	if (mLastKey == mKey["arrow"])
		mLastKey = _getch();
}


void Keyboard::DynamicInput()
{
	if (_kbhit())
	{
		mLastKey = _getch();

		if (mLastKey == mKey["arrow"])
			mLastKey = _getch();
	}
}


bool Keyboard::IsPressed(string key)
{
	if (mLastKey == mKey[key])
		return true;

	return false;
}

void Keyboard::Clear()
{
	mLastKey = 0;
}


Keyboard* Keyboard::s_instance = nullptr;

Keyboard* Keyboard::Instance()
{
	if (s_instance == nullptr)
		s_instance = new Keyboard;

	return s_instance;
}

void Keyboard::Release()
{
	delete s_instance;
	s_instance = nullptr;
}