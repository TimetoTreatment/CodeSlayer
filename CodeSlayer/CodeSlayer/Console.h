#pragma once
#include <windows.h>
#include <iostream>

using namespace std;

class Console
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	/* Change Color Name to Integer */
	int ColorNameToNumber(const string& colorName) const;

public:

	/* Set Console Cursor Position */
	void CursorPosition(int x, int y);

	/* Set Text Color */
	void Color(const string& foreground = "default", const string& background = "default");

	/* Clear CMD Console */
	void Clear();


private:
	static Console* s_instance;

public:
	static Console* Instance();
	static void Release();
};
