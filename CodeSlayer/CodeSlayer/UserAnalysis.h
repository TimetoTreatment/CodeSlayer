#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Random.h"

using namespace std;


class UserAnalysis
{
private:

	enum class FieldType
	{
		keyword,
		header,
		function
	};

	Random* mRandom;

	unsigned int mWordNum = 50;

	const unsigned int mWordKeywordNum = 25;
	const unsigned int mWordHeaderNum = 5;
	const unsigned int mWordFunctionNum = 20;

	const unsigned int mWordKeywordWeight = 5;
	const unsigned int mWordHeaderWeight = 1;
	const unsigned int mWordFunctionWeight = 4;

	unsigned int mWordKeywordProbability = 100;
	unsigned int mWordHeaderProbability = 20;
	unsigned int mWordFunctionProbability = 80;
	unsigned int mWordTotalProbability;

	const unsigned int mShortNum = 30;

	const unsigned int mShortKeywordNum = 5;
	const unsigned int mShortHeaderNum = 5;
	const unsigned int mShortFunctionNum = 20;

	const unsigned int mShortKeywordWeight = 1;
	const unsigned int mShortHeaderWeight = 1;
	const unsigned int mShortFunctionWeight = 4;

	unsigned int mShortKeywordProbability = 20;
	unsigned int mShortHeaderProbability = 20;
	unsigned int mShortFunctionProbability = 80;
	unsigned int mShortTotalProbability;

	vector<FieldType> mWordProbabilities;
	vector<FieldType> mShortProbabilities;


public:

	UserAnalysis();

	void ReadFile();

	void UpdateProbability(const string& practiceType, unsigned int index, bool isCorrect);

	void SetAnalyzedContainer(const string& type);

	int GetAnalyzedFieldType(const string& type);


private:
	static UserAnalysis* sInstance;

public:
	static UserAnalysis* Instance();
	static void Release();
};
