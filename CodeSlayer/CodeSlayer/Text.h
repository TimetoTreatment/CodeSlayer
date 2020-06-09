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

public:

	Text();

	/* 문자열 저장 */
	void SetText(string t);

	/* 문자열 반환  */
	string GetText() const;

	/* 문자열 길이 저장 */
	void SetTextLength(int tl);

	/* 문자열 길이 반환 */
	int GetTextLength() const;
};