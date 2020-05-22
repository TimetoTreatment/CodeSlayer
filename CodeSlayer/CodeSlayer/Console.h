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

	/* Ŀ�� ��ġ ���� */
	void CursorPosition(int x, int y);

	/* �ؽ�Ʈ �� ���� */
	void Color(const string& foreground = "default", const string& background = "default");

	/* �ܼ� â�� ��� ���� ���� */
	void Clear();

	/* ���� Ŀ�� ��ġ���� (���������� x, �Ʒ��� y) ũ���� ��� ���� ���� */
	void Clear(int startX, int startY, int width, int height);


private:
	static Console* sInstance;

public:
	static Console* Instance();
	static void Release();
};
