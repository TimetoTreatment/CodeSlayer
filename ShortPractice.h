#pragma once
#include "TypingManager.h"


class ShortPractice : public TypingManager
{
private:

	ShortPractice() {
		Instance();
	}

public:

	void Main();


private:
	static ShortPractice* sInstance;

public:
	static ShortPractice* Instance();
	static void Release();
};