#include "Keyboard.h"



Keyboard::Keyboard()
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
