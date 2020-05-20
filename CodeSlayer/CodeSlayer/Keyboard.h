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

	void StaticInput()
	{
		mLastKey = _getch();

		if (mLastKey == mKey["arrow"])
			mLastKey = _getch();
	}


	void DynamicInput()
	{
		if (_kbhit())
		{
			mLastKey = _getch();
		}
	}


	bool IsPressed(string key)
	{
		if (mLastKey == mKey[key])
			return true;

		return false;
	}

	void Clear()
	{
		mLastKey = 0;
	}





private:
	static Keyboard* s_instance;

public:
	static Keyboard* Instance();
	static void Release();
};

