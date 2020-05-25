#pragma once
#include "TypingManager.h"


class LongPractice : public TypingManager
{
private:

	LongPractice() {}


public:

	void Main() {}


private:
	static LongPractice* sInstance;

public:
	static LongPractice* Instance();
	static void Release();
};
