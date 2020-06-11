#pragma once
#include <string>

using namespace std;

class Text {

private:

	string mText;
	int mLength;

public:

	Text();

	/* ���ڿ� ���� */
	void SetText(string text);

	/* ���ڿ� ��ȯ  */
	string GetText() const;

	/* ���ڿ� ���� ���� */
	void SetTextLength(int length);

	/* ���ڿ� ���� ��ȯ */
	int GetTextLength() const;
};