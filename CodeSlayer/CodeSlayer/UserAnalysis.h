#pragma once
#include <iostream>

using namespace std;


class UserAnalysis
{
private:


	unsigned int Word = 50;

	const unsigned int WordKeyword = 25;
	const unsigned int WordHeader = 5;
	const unsigned int WordFunction = 20;

	const unsigned int WordKeywordWeight = 5;
	const unsigned int WordHeaderWeight = 1;
	const unsigned int WordFunctionWeight = 4;

	unsigned int WordKeywordProbability;
	unsigned int WordHeaderProbability;
	unsigned int WordFunctionProbability;


	const unsigned int Short = 40;

	const unsigned int ShortKeyShort = 5;
	const unsigned int ShortHeader = 5;
	const unsigned int ShortFunction = 20;

	const unsigned int ShortKeyShortWeight = 1;
	const unsigned int ShortHeaderWeight = 1;
	const unsigned int ShortFunctionWeight = 4;

	unsigned int ShortKeyShortProbability;
	unsigned int ShortHeaderProbability;
	unsigned int ShortFunctionProbability;


public:

	UserAnalysis()
	{
		WordKeywordProbability = 100;
		WordHeaderProbability = 20;
		WordFunctionProbability = 80;

		ShortKeyShortProbability = 20;
		ShortHeaderProbability = 20;
		ShortFunctionProbability = 80;
	}

	









private:
	static UserAnalysis* sInstance;

public:
	static UserAnalysis* Instance();
	static void Release();

};

