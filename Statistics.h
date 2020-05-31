#pragma once
#include "Text.h"
#include "ProgramManager.h"
#include "WordPractice.h"
#include "ShortPractice.h"
#include "LongPractice.h"

class Statistics {
private:
	Statistics *sInstance=nullptr;

	fstream file;
	Text forWords;
	Text forShort;
	Text forLong;

public:
	Statistics() {};
	Statistics* Instance();
	void setInfo(WordPractice *ins);
	void setInfo(ShortPractice *ins);
	void setInfo(LongPractice *ins);
	void printStatus();
};