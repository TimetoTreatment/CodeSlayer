#include "UserAnalysis.h"




UserAnalysis::UserAnalysis()
{
	mRandom = Random::Instance();

	mWordTotalProbability = mWordKeywordProbability + mWordHeaderProbability + mWordFunctionProbability;
	mShortTotalProbability = mShortKeywordProbability + mShortHeaderProbability + mShortFunctionProbability;

}



void UserAnalysis::UpdateProbability(const string& practiceType, unsigned int index, bool isCorrect)
{
	int multiplier = (isCorrect ? -1 : 2);

	if (practiceType == "word")
	{
		if (0 <= index && index < mWordKeyword)
		{
			mWordKeywordProbability += mWordKeywordWeight * multiplier;

			if (mWordKeywordProbability < mWordKeyword * 4)
				mWordKeywordProbability = mWordKeyword * 4;
		}

		else if (mWordKeyword <= index && index < mWordKeyword + mWordHeader)
		{
			mWordHeaderProbability += mWordHeaderWeight * multiplier;

			if (mWordHeaderProbability < mWordHeader * 4)
				mWordHeaderProbability = mWordHeader * 4;
		}

		else
		{
			mWordFunctionProbability += mWordFunctionWeight * multiplier;

			if (mWordFunctionProbability < mWordFunction * 4)
				mWordFunctionProbability = mWordFunction * 4;
		}
	}

	else if (practiceType == "short")
	{
		if (0 <= index && index < mShortKeyword)
		{
			mShortKeywordProbability += mShortKeywordWeight * multiplier;

			if (mShortKeywordProbability < mShortKeyword * 4)
				mShortKeywordProbability = mShortKeyword * 4;
		}

		else if (mShortKeyword <= index && index < mShortKeyword + mShortHeader)
		{
			mShortHeaderProbability += mShortHeaderWeight * multiplier;

			if (mShortHeaderProbability < mShortHeader * 4)
				mShortHeaderProbability = mShortHeader * 4;
		}

		else
		{
			mShortFunctionProbability += mShortFunctionWeight * multiplier;

			if (mShortFunctionProbability < mShortFunction * 4)
				mShortFunctionProbability = mShortFunction * 4;
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
			return mRandom->Integer(0, mWordKeyword - 1);

		case FieldType::header:
			return mRandom->Integer(mWordKeyword, mWordKeyword + mWordHeader - 1);

		case FieldType::function:
			return mRandom->Integer(mWordKeyword + mWordHeader, mWord - 1);
		}
	}

	else if (type == "short")
	{
		switch (mShortProbabilities[mRandom->Integer(0, mShortTotalProbability - 1)])
		{
		case FieldType::keyword:
			return mRandom->Integer(0, mShortKeyword - 1);

		case FieldType::header:
			return mRandom->Integer(mShortKeyword, mShortKeyword + mShortHeader - 1);

		case FieldType::function:
			return mRandom->Integer(mShortKeyword + mShortHeader, mShort - 1);
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

