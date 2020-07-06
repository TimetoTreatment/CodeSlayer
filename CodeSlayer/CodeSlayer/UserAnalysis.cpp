#include "UserAnalysis.h"


UserAnalysis::UserAnalysis()
{
	mRandom = Random::Instance();

	mWordTotalProbability = mWordKeywordProbability + mWordHeaderProbability + mWordFunctionProbability;
	mShortTotalProbability = mShortKeywordProbability + mShortHeaderProbability + mShortFunctionProbability;

	ReadFile();
}


void UserAnalysis::ReadFile()
{
	fstream file("throwing.txt", ios::in);

	if (!file.good())
		return;

	string fieldType;

	getline(file, fieldType);

	if (fieldType == "keyword")
	{
		mWordKeywordProbability += mWordKeywordWeight * 10;
		mShortKeywordProbability += mShortKeywordWeight * 10;
	}
	else if (fieldType == "header")
	{
		mWordHeaderProbability += mWordHeaderWeight * 10;
		mShortHeaderProbability += mShortHeaderWeight * 10;
	}
	else if (fieldType == "function")
	{
		mWordFunctionProbability += mWordFunctionWeight * 10;
		mShortFunctionProbability += mShortFunctionWeight * 10;
	}

	file.close();
}


void UserAnalysis::UpdateProbability(const string& practiceType, unsigned int index, bool isCorrect)
{
	int multiplier = (isCorrect ? -1 : 2);

	if (practiceType == "word")
	{
		if (0 <= index && index < mWordKeywordNum)
		{
			mWordKeywordProbability += mWordKeywordWeight * multiplier;

			if (mWordKeywordProbability < mWordKeywordNum * 4)
				mWordKeywordProbability = mWordKeywordNum * 4;
		}

		else if (mWordKeywordNum <= index && index < mWordKeywordNum + mWordHeaderNum)
		{
			mWordHeaderProbability += mWordHeaderWeight * multiplier;

			if (mWordHeaderProbability < mWordHeaderNum * 4)
				mWordHeaderProbability = mWordHeaderNum * 4;
		}

		else
		{
			mWordFunctionProbability += mWordFunctionWeight * multiplier;

			if (mWordFunctionProbability < mWordFunctionNum * 4)
				mWordFunctionProbability = mWordFunctionNum * 4;
		}
	}

	else if (practiceType == "short")
	{
		if (0 <= index && index < mShortKeywordNum)
		{
			mShortKeywordProbability += mShortKeywordWeight * multiplier;

			if (mShortKeywordProbability < mShortKeywordNum * 4)
				mShortKeywordProbability = mShortKeywordNum * 4;
		}

		else if (mShortKeywordNum <= index && index < mShortKeywordNum + mShortHeaderNum)
		{
			mShortHeaderProbability += mShortHeaderWeight * multiplier;

			if (mShortHeaderProbability < mShortHeaderNum * 4)
				mShortHeaderProbability = mShortHeaderNum * 4;
		}

		else
		{
			mShortFunctionProbability += mShortFunctionWeight * multiplier;

			if (mShortFunctionProbability < mShortFunctionNum * 4)
				mShortFunctionProbability = mShortFunctionNum * 4;
		}
	}

	else
	{
		cout << "UserAnalysis::UpdateProbability";
		exit(-1);
	}
}


void UserAnalysis::SetAnalyzedContainer(const string& type)
{
	if (type == "word")
	{
		mWordTotalProbability = mWordKeywordProbability + mWordHeaderProbability + mWordFunctionProbability;

		mWordProbabilities.clear();

		mWordProbabilities.resize(mWordKeywordProbability, FieldType::keyword);
		mWordProbabilities.resize(mWordKeywordProbability + mWordHeaderProbability, FieldType::header);
		mWordProbabilities.resize(mWordKeywordProbability + mWordHeaderProbability + mWordFunctionProbability, FieldType::function);
	}

	else if (type == "short")
	{
		mShortTotalProbability = mShortKeywordProbability + mShortHeaderProbability + mShortFunctionProbability;

		mShortProbabilities.clear();

		mShortProbabilities.resize(mShortKeywordProbability, FieldType::keyword);
		mShortProbabilities.resize(mShortKeywordProbability + mShortHeaderProbability, FieldType::header);
		mShortProbabilities.resize(mShortKeywordProbability + mShortHeaderProbability + mShortFunctionProbability, FieldType::function);
	}

	else
	{
		cout << "UserAnalysis::SetAnalyzedContainer()";
		exit(-1);
	}
}


int UserAnalysis::GetAnalyzedFieldType(const string& type)
{
	if (type == "word")
	{
		switch (mWordProbabilities[mRandom->Integer(0, mWordTotalProbability - 1)])
		{
		case FieldType::keyword:
			return mRandom->Integer(0, mWordKeywordNum - 1);

		case FieldType::header:
			return mRandom->Integer(mWordKeywordNum, mWordKeywordNum + mWordHeaderNum - 1);

		case FieldType::function:
			return mRandom->Integer(mWordKeywordNum + mWordHeaderNum, mWordNum - 1);
		}
	}

	else if (type == "short")
	{
		switch (mShortProbabilities[mRandom->Integer(0, mShortTotalProbability - 1)])
		{
		case FieldType::keyword:
			return mRandom->Integer(0, mShortKeywordNum - 1);

		case FieldType::header:
			return mRandom->Integer(mShortKeywordNum, mShortKeywordNum + mShortHeaderNum - 1);

		case FieldType::function:
			return mRandom->Integer(mShortKeywordNum + mShortHeaderNum, mShortNum - 1);
		}
	}

	cout << "UserAnalysis::GetAnalyzedIndex()";
	exit(-1);
}


UserAnalysis* UserAnalysis::sInstance = nullptr;

UserAnalysis* UserAnalysis::Instance()
{
	if (sInstance == nullptr)
		sInstance = new UserAnalysis;

	return sInstance;
}

void UserAnalysis::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

