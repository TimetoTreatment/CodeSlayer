#pragma once
#include "TypingManager.h"


class WordPractice : public TypingManager
{
private:
	WordPractice() {
		Instance();
	}

public:

	void Main();


private:
	static WordPractice* sInstance;

public:
	static WordPractice* Instance();
	static void Release();
};