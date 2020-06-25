//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 텍스트
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 프로그램에서 사용하는 프리셋 코드 저장

	2. 기능
		- 일반적인 문자열과 구별 가능
		- 추후 필요한 기능 추가 예정
*/

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