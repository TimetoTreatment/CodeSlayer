#pragma once
#include "TypingManager.h"


class WordPractice : public TypingManager
{
private:



public:

	void Main();


private:
	static WordPractice* sInstance;

public:
	static WordPractice* Instance();
	static void Release();
};

