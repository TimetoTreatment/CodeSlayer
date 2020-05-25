#pragma once
#include <windows.h>
#include <iostream>

using namespace std;

class Console
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string mEraser;

	/* Change Color Name to Integer */
	int ColorNameToNumber(const string& colorName) const;

public:

	/* 커서 위치 지정 */
	void CursorPosition(int x, int y);

	/* 텍스트 색 지정 */
	void Color(const string& foreground = "default", const string& background = "default");

	/* 콘솔 창의 모든 문자 제거 */
	void Clear();

	/* 현재 커서 위치에서 (오른쪽으로 x, 아래로 y) 크기의 모든 문자 제거 */
	void Clear(int startX, int startY, int width, int height);


private:
	static Console* sInstance;

public:
	static Console* Instance();
	static void Release();
};
