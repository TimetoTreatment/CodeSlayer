#include "TypingManager.h"


/* static 변수 초기화 */
vector<Text>* TypingManager::mWords = nullptr;
vector<Text>* TypingManager::mShorts = nullptr;
vector<Text>* TypingManager::mLongs = nullptr;
bool TypingManager::sTextVectorLoaded = false;

vector<int>* TypingManager::mRandomTableWord = nullptr;
vector<int>* TypingManager::mRandomTableShort = nullptr;
vector<int>* TypingManager::mRandomTableLong = nullptr;


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
		path = "Assets/preset/long/long" + to_string(count) + ".txt";
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


void TypingManager::SetRandomTable(const string& type)
{
	int count;
	int shuffleCount;
	int randomIndex1;
	int randomIndex2;
	int temp;

	if (type == "word")
	{
		mRandomTableWord->clear();

		for (count = 0; count < FileNum::Word; count++)
			mRandomTableWord->emplace_back(count);

		shuffleCount = FileNum::Word * 2;

		for (count = 0; count < shuffleCount; count++)
		{
			randomIndex1 = Random::Integer(0, FileNum::Word - 1);
			randomIndex2 = Random::Integer(0, FileNum::Word - 1);

			temp = mRandomTableWord->at(randomIndex1);
			mRandomTableWord->at(randomIndex1) = mRandomTableWord->at(randomIndex2);
			mRandomTableWord->at(randomIndex2) = temp;
		}
	}

	else if (type == "short")
	{
		mRandomTableShort->clear();

		for (count = 0; count < FileNum::Short; count++)
			mRandomTableShort->emplace_back(count);

		shuffleCount = FileNum::Short * 2;

		for (count = 0; count < shuffleCount; count++)
		{
			randomIndex1 = Random::Integer(0, FileNum::Short - 1);
			randomIndex2 = Random::Integer(0, FileNum::Short - 1);

			temp = mRandomTableShort->at(randomIndex1);
			mRandomTableShort->at(randomIndex1) = mRandomTableShort->at(randomIndex2);
			mRandomTableShort->at(randomIndex2) = temp;
		}
	}

	else if (type == "long")
	{
		mRandomTableLong->clear();

		for (count = 0; count < FileNum::Long; count++)
			mRandomTableLong->emplace_back(count);

		shuffleCount = FileNum::Long * 2;

		for (count = 0; count < shuffleCount; count++)
		{
			randomIndex1 = Random::Integer(0, FileNum::Long - 1);
			randomIndex2 = Random::Integer(0, FileNum::Long - 1);

			temp = mRandomTableLong->at(randomIndex1);
			mRandomTableLong->at(randomIndex1) = mRandomTableLong->at(randomIndex2);
			mRandomTableLong->at(randomIndex2) = temp;
		}
	}

	else
	{
		cout << "Error | TypingManager::SetRandomTable(const string& type)\n\n";
		exit(-1);
	}
}


int TypingManager::GetRandomTableNum(const string& type)
{
	mRandomTableIndex++;

	if (type == "word")
	{
		if (mRandomTableIndex == FileNum::Word)
		{
			SetRandomTable("word");
			mRandomTableIndex = 0;
		}

		return mRandomTableWord->at(mRandomTableIndex);
	}

	else if (type == "short")
	{
		if (mRandomTableIndex == FileNum::Short)
		{
			SetRandomTable("short");
			mRandomTableIndex = 0;
		}

		return mRandomTableShort->at(mRandomTableIndex);
	}

	else if (type == "long")
	{
		if (mRandomTableIndex == FileNum::Long)
		{
			SetRandomTable("long");
			mRandomTableIndex = 0;
		}

		return mRandomTableLong->at(mRandomTableIndex);
	}

	else
	{
		cout << "Error | TypingManager::GetRandomTableNum(const string& type)\n\n";
		exit(-1);
	}
}


TypingManager::TypingManager()
{
	if (sTextVectorLoaded == false)
	{
		mWords = new vector<Text>;
		mShorts = new vector<Text>;
		mLongs = new vector<Text>;
		sTextVectorLoaded = true;

		LoadTextFiles();

		mRandomTableWord = new vector<int>;
		mRandomTableShort = new vector<int>;
		mRandomTableLong = new vector<int>;

		SetRandomTable("word");
		SetRandomTable("short");
		SetRandomTable("long");
	}

	mRandomTableIndex = 0;

	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();
	mTimer = new Timer;

	mTypingSpeed = 0;
	mTypingAccuracy = 100;
}


TypingManager::~TypingManager()
{
	delete mWords;
	delete mShorts;
	delete mLongs;
	delete mTimer;
	delete mRandomTableWord;
	delete mRandomTableShort;
	delete mRandomTableLong;

	mWords = nullptr;
	mShorts = nullptr;
	mLongs = nullptr;
	mTimer = nullptr;
	mRandomTableWord = nullptr;
	mRandomTableShort = nullptr;
	mRandomTableLong = nullptr;
}


Text TypingManager::GetRandomText(const string& type)
{
	if (type == "word")
		return mWords->at(GetRandomTableNum("word"));

	else if (type == "short")
		return mShorts->at(GetRandomTableNum("short"));

	else if (type == "long")
		return mLongs->at(GetRandomTableNum("long"));

	else
	{
		cout << "Error | TypingManager::GetRandomText(const string& type)\n\n";
		exit(-1);
	}
}
