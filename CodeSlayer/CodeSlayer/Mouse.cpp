#include "Mouse.h"









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