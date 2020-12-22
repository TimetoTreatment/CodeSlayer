//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// �ܼ� ��� ����
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- �ܼ� ��� ����
		- �ڵ��� ���̸� ���� �� ����

	2. ���
		- ��� Ŀ�� ��ġ ����
		- ��� ���� ����
		- �ܼ� â ��ü �Ǵ� �Ϻ� ����
		- �ؽ�Ʈ ���� ���
		- �� ����� ��� ��ģ ���� ���
*/

#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Console
{
private:

	HANDLE mHandleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO mCursor;
	string mEraser;

	/* ���� ���ڿ��� ������ ��ȯ */
	int ColorNameToNumber(const string& colorName) const;

	Console() 
	{
		mCursor.dwSize = 100;
		mCursor.bVisible = FALSE;
	}
	~Console() {}


public:

	/* Ŀ�� ǥ�� */
	void CursorVisible(bool visible);

	/* Ŀ�� ��ġ ���� */
	void CursorPosition(int x, int y);

	/* �ؽ�Ʈ �� ���� */
	void Color(const string& foreground = "default", const string& background = "default");

	/* �ܼ� â ���� */
	void Clear();

	/* �ܼ� â �Ϻ� ���� */
	void Clear(int XPosStart, int YPosStart, int width, int height);

	/* ���ڿ� �Ǵ� ���� ��� */
	void Draw(string str_or_file, const char* color, int startX, int startY);


private:
	static Console* sInstance;

public:
	static Console* Instance();
	static void Release();
};


