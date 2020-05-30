#pragma once
#include "TypingManager.h"


class LongPractice : public TypingManager
{
private:

	LongPractice() {}
	int mTestCase = 3;

public:

	void Main();


private:
	static LongPractice* sInstance;

public:
	static LongPractice* Instance();
	static void Release();
};
