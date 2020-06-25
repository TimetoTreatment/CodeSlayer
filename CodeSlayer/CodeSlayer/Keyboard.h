//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 키보드
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 키보드 입력 확인
		- 화살표 키 등 특수키 인식

	2. 기능
		- 사용자의 입력을 기다리는 정적 입력
		- 사용자의 입력을 감지하는 동적 입력
*/

#pragma once
#include <conio.h>
#include <string>
#include <unordered_map>

using namespace std;


class Keyboard
{
private:

	int mLastKey;

	/* 키보드 키 문자열을 정수로 변환 */
	unordered_map<string, unsigned int> mKey = {
		{"enter", 13},
		{"arrow", 224},
		{"up", 72},
		{"down", 80},
		{"left", 75},
		{"right", 77},
	};

	Keyboard();
	~Keyboard() {}

public:

	/* 정적 입력 */
	void StaticInput();

	/* 동적 입력*/
	void DynamicInput();

	/* 입력 확인 */
	bool IsPressed(string key);

	/* 입력 초기화 */
	void Clear();


private:
	static Keyboard* s_instance;

public:
	static Keyboard* Instance();
	static void Release();
};

