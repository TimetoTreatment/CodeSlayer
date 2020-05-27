#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Text {

private:

	string text;
	int textLength;
	bool isUsed;

public:

	Text();

	/* ���ڿ� ���� */
	void SetText(string t);

	/* ���ڿ� ��ȯ  */
	string GetText() const;

	/* ���ڿ� ���� ���� */
	void SetTextLength(int tl);

	/* ���ڿ� ���� ��ȯ */
	int GetTextLength() const;

	/* ���� ���ڿ��� ���� */
	void IsUsed();

	/* ���Ǿ����� ��ȯ */
	bool GetIsUsed() const;
};