#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Console
{
private:

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string mEraser;

	/* Change Color Name to Integer */
	int ColorNameToNumber(const string& colorName) const;

	Console() {}
	~Console() {}


public:

	/* 커서 위치 지정 */
	void CursorPosition(int x, int y);

	/* 텍스트 색 지정 */
	void Color(const string& foreground = "default", const string& background = "default");

	/* 콘솔 창 비우기 */
	void Clear();

	/* 콘솔 창 일부 비우기 */
	void Clear(int startX, int startY, int width, int height);

	/* 문자열 또는 파일 출력 */
	void Draw(string str_or_file, const char* color, int startX, int startY);


private:
	static Console* sInstance;

public:
	static Console* Instance();
	static void Release();
};
