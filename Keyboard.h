#pragma once
#include <conio.h>
#include <string>
#include <unordered_map>

using namespace std;


class Keyboard
{
private:

	unordered_map<string, unsigned int> mKey = {
		{"enter", 13},
		{"arrow", 224},
		{"up", 72},
		{"down", 80},
		{"left", 75},
		{"right", 77},
	};

	int mLastKey;


public:

	Keyboard();

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

