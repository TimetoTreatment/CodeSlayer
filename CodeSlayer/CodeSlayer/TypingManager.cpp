#include "TypingManager.h"

////////////////////////
/* static ���� �ʱ�ȭ */
////////////////////////
bool TypingManager::sTextVectorLoaded = false;

vector<Text>* TypingManager::mWords = nullptr;
vector<Text>* TypingManager::mShorts = nullptr;
vector<Text>* TypingManager::mLongs = nullptr;

vector<int>* TypingManager::mRandomTableWord = nullptr;
vector<int>* TypingManager::mRandomTableShort = nullptr;
vector<int>* TypingManager::mRandomTableLong = nullptr;


/////////////////////////////
/* ������ �ؽ�Ʈ ���� �ε� */
/////////////////////////////
void TypingManager::LoadTextFiles()
{
	int count;
	Text newText;
	string path;
	string line;
	string longText;
	fstream file;

	file.open("Assets/preset/word.txt");	// �ܾ� ������ �ؽ�Ʈ ���� ����

	for (count = 0; count < FileNum::Word; count++)	// ȯ�� ������ ���ǵ� "�ܾ��� ��" ��ŭ �ݺ�
	{
		getline(file, line);						// �ܾ� �� ���� �о�

		newText.SetText(line);						// �ؽ�Ʈ ��ü�� ����
		newText.SetTextLength(line.length());		// �ؽ�Ʈ ��ü�� ���ڿ� ���� ����

		mWords->emplace_back(newText);				// �ܾ� ���Ϳ� �ؽ�Ʈ ��ü ����
	}

	file.close();
	file.open("Assets/preset/short.txt");	// ª�� �� ������ �ؽ�Ʈ ���� ����

	for (count = 0; count < FileNum::Short; count++)
	{
		getline(file, line);

		newText.SetText(line);
		newText.SetTextLength(line.length());

		mShorts->emplace_back(newText);
	}

	file.close();

	for (count = 0; count < FileNum::Long; count++)						// ȯ�� ������ ���ǵ� "�� ���� ��" ��ŭ �ݺ�
	{
		path = "Assets/preset/long/long" + to_string(count) + ".txt";	// �� ������ ��η� ����

		file.open(path);							// �� �� ������ �ؽ�Ʈ ���� ����

		if (!file.good())							// ���� ó��
		{
			cout << "Cannot Open " << path;
			exit(-1);
		}

		for (longText.clear(); !file.eof();)		// ������ ������
		{
			getline(file, line);					// �� �� �о�
			longText += line + '\n';				// �� �� ���ڿ��� �߰�
		}

		newText.SetText(longText);					// �ؽ�Ʈ ��ü�� �� �� ���ڿ��� ����
		newText.SetTextLength(longText.length());	// ���ڿ��� ���� ����

		mLongs->emplace_back(newText);				// �� �� ���Ϳ� �ؽ�Ʈ ��ü ����
		file.close();								// ���� �ݱ�
	}
}


//////////////////////
/* ���� ���̺� ���� */
//////////////////////
void TypingManager::SetRandomTable(const string& type)
{
	int temp;
	int count;
	int shuffleCount;
	int randomIndex1;
	int randomIndex2;

	if (type == "word")						// ���ڰ� �ܾ��� ��
	{
		shuffleCount = FileNum::Word * 2;							// ������ �ܾ� ���� 2�踸ŭ �ݺ�

		for (count = 0; count < shuffleCount; count++)				// ���� ���̺� �ڼ��� �ݺ���
		{
			randomIndex1 = Random::Integer(0, FileNum::Word - 1);	// ������ �ε��� ����
			randomIndex2 = Random::Integer(0, FileNum::Word - 1);	// ������ �ε��� ����

			temp = mRandomTableWord->at(randomIndex1);				// ���̺� �� �� �ε��� ����
			mRandomTableWord->at(randomIndex1) = mRandomTableWord->at(randomIndex2);
			mRandomTableWord->at(randomIndex2) = temp;
		}
	}

	else if (type == "short")
	{
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

	else	// ���� ó��
	{
		cout << "Error | TypingManager::SetRandomTable(const string& type)\n\n";
		exit(-1);
	}
}


/////////////////////////
/* ���� ���̺� �� ��ȯ */
/////////////////////////
int TypingManager::GetRandomTableNum(const string& type)
{
	mRandomTableIndex++;	// ���̺� �ε��� ����
	
	if (type == "word")									// ���ڰ� �ܾ��� ��
	{
		if (mRandomTableIndex == FileNum::Word)			// ���̺��� ������ �������� ����Ͽ��ٸ�
		{
			SetRandomTable("word");						// ���� ���̺��� �ٽ� ����
			mRandomTableIndex = 0;						// �ε��� �ʱ�ȭ
		}

		return mRandomTableWord->at(mRandomTableIndex);	// ���̺�[�ε���] ��ȯ 
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

	else	// ���� ó��
	{
		cout << "Error | TypingManager::GetRandomTableNum(const string& type)\n\n";
		exit(-1);
	}
}


////////////
/* ������ */
////////////
TypingManager::TypingManager()
{
	if (sTextVectorLoaded == false)				// ������ �ؽ�Ʈ ������ �ε��� ���� ���ٸ�
	{
		sTextVectorLoaded = true;				// �÷��� ������Ʈ

		mWords = new vector<Text>;				// �ܾ� ���� ����
		mShorts = new vector<Text>;				// ª�� �� ���� ����
		mLongs = new vector<Text>;				// �� �� ���� ����

		LoadTextFiles();						// ������ �ؽ�Ʈ ���� �ε�

		mRandomTableWord = new vector<int>;		// �ܾ� ���� ���̺� ���� ����
		mRandomTableShort = new vector<int>;	// ª�� �� ���� ���̺� ���� ����
		mRandomTableLong = new vector<int>;		// �� �� ���� ���̺� ���� ����

		int count;

		/* ���̺� �ʱ�ȭ */
		for (count = 0; count < FileNum::Word; count++)
			mRandomTableWord->emplace_back(count);		

		for (count = 0; count < FileNum::Short; count++)
			mRandomTableShort->emplace_back(count);

		for (count = 0; count < FileNum::Long; count++)
			mRandomTableLong->emplace_back(count);

		/* ���� ���̺� ���� */
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


////////////
/* �Ҹ��� */
////////////
TypingManager::~TypingManager()
{
	sTextVectorLoaded = false;

	delete mTimer;
	delete mWords;				// ���� ����
	delete mShorts;				//
	delete mLongs;				//
	delete mRandomTableWord;	//
	delete mRandomTableShort;	//
	delete mRandomTableLong;	//

	mTimer = nullptr;
	mWords = nullptr;				// nullptr�� �ƴ϶�� 
	mShorts = nullptr;				// ���� �Ļ� Ŭ������ �Ҹ�� ��
	mLongs = nullptr;				// delete���� ���� �߻�
	mRandomTableWord = nullptr;		// 
	mRandomTableShort = nullptr;	//
	mRandomTableLong = nullptr;		//
}


///////////////////////////////
/* ������ ������ �ؽ�Ʈ ��ȯ */
///////////////////////////////
Text TypingManager::GetRandomText(const string& type)
{
	if (type == "word")
		return mWords->at(GetRandomTableNum("word"));	// �ܾ�[����]�� �ؽ�Ʈ ��ü ��ȯ

	else if (type == "short")
		return mShorts->at(GetRandomTableNum("short"));	// ª����[����]�� �ؽ�Ʈ ��ü ��ȯ

	else if (type == "long")
		return mLongs->at(GetRandomTableNum("long"));	// ���[����]�� �ؽ�Ʈ ��ü ��ȯ

	else
	{
		cout << "Error | TypingManager::GetRandomText(const string& type)\n\n";
		exit(-1);
	}
}
