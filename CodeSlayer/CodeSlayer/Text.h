#pragma once
#include <string>

using namespace std;

class Text {

private:

	string mText;
	int mLength;

public:

	Text();

	/* 문자열 저장 */
	void SetText(string text);

	/* 문자열 반환  */
	string GetText() const;

	/* 문자열 길이 저장 */
	void SetTextLength(int length);

	/* 문자열 길이 반환 */
	int GetTextLength() const;
};