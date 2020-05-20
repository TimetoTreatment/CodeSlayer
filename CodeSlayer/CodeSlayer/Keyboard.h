#pragma once
#include <string>
#include <conio.h>
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

	/* ���� �Է� */
	void StaticInput();

	/* ���� �Է�*/
	void DynamicInput();

	/* �ش� Ű�� �ֽ� �Է����� Ȯ�� */
	bool IsPressed(string key);

	/* �ֽ� �Է� �ʱ�ȭ */
	void Clear();


private:
	static Keyboard* s_instance;

public:
	static Keyboard* Instance();
	static void Release();
};

