#include "TypingManager.h"

void TypingManager::LoadTextFiles()
{
	int count;
	string path;
	string line;
	string longText;
	Text newText;
	fstream file;

	file.open("Assets/preset/word.txt");

	for (count = 0; count < FileNum::Word; count++)
	{
		getline(file, line);

		newText.SetText(line);
		newText.SetTextLength(line.length());

		mWords->push_back(newText);
	}

	file.close();
	file.open("Assets/preset/short.txt");

	for (count = 0; count < FileNum::Short; count++)
	{
		getline(file, line);

		newText.SetText(line);
		newText.SetTextLength(line.length());

		mShorts->push_back(newText);
	}

	file.close();

	for (count = 0; count < FileNum::Long; count++)
	{
		path = "Assets/preset/long" + to_string(count) + ".txt";
		file.open(path);

		if (!file.is_open())
		{
			cout << "Cannot Open " << path;
			exit(-1);
		}

		for (longText.clear(); !file.eof();)
		{
			getline(file, line);
			longText += line + '\n';
		}

		newText.SetText(longText);
		newText.SetTextLength(longText.length());

		mLongs->push_back(newText);
		file.close();
	}
}


TypingManager::TypingManager()
{
	startTime = 0;
	typeSpeed = 0;
	typeaccuracy = 0;
	timetake = 0;
	correct_cnt = 0;
	answer_cnt = 0;
	typenum = 0;
	ans = '\0';
	pracType = 0;
	mRandomIndex = 0;

	if (sTextVectorLoaded == false)	// 로드된 적이 없다면
	{
		mAns = new vector<char>;	// 새 백터 객체 생성
		mWords = new vector<Text>;
		mShorts = new vector<Text>;
		mLongs = new vector<Text>;
		sTextVectorLoaded = true;

		LoadTextFiles();			// 파일을 로딩해 벡터에 저장합니다.
	}
}


TypingManager::~TypingManager()
{
	delete mAns;
	delete mWords;
	delete mShorts;
	delete mLongs;

	mAns = nullptr;
	mWords = nullptr;
	mShorts = nullptr;
	mLongs = nullptr;
}


/* static 변수 5개 초기화 */
vector<char>* TypingManager::mAns = nullptr;
vector<Text>* TypingManager::mWords = nullptr;
vector<Text>* TypingManager::mShorts = nullptr;
vector<Text>* TypingManager::mLongs = nullptr;
bool TypingManager::sTextVectorLoaded = false;


Text TypingManager::GetRandomText(const string& type)
{
	if (type == "word")
	{
		do {
			mRandomIndex = Random::Integer(0, FileNum::Word - 1);
		} while (mWords->at(mRandomIndex).GetIsUsed());

		mWords->at(mRandomIndex).IsUsed();
		return mWords->at(mRandomIndex);
	}

	else if (type == "short")
	{
		do {
			mRandomIndex = Random::Integer(0, FileNum::Short - 1);
		} while (mShorts->at(mRandomIndex).GetIsUsed());

		mShorts->at(mRandomIndex).IsUsed();
		return mShorts->at(mRandomIndex);
	}

	else if (type == "long")
	{
		do {
			mRandomIndex = Random::Integer(0, FileNum::Long - 1);
		} while (mLongs->at(mRandomIndex).GetIsUsed());

		mLongs->at(mRandomIndex).IsUsed();
		return mLongs->at(mRandomIndex);
	}

	else if (type == "game")
	{
		do {
			mRandomIndex = Random::Integer(0, FileNum::Game - 1);
		} while (mLongs->at(mRandomIndex).GetIsUsed());

		mLongs->at(mRandomIndex).IsUsed();
		return mLongs->at(mRandomIndex);
	}

	else
	{
		cout << "Error | TypingManager::GetRandomText(const string& type)\n\n";
		exit(-1);
	}
}


