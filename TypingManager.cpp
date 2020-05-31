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
	mInstance->Instance();
	typeSpeed = 0;
	typeaccuracy = 0;
	timetake = 0;
	correct_cnt = 0;
	answer_cnt = 0;
	typenum = 0;
	ans = '\0';
	pracType = 0;
	mRandomIndex = 0;

	if (sTextVectorLoaded == false)	// �ε�� ���� ���ٸ�
	{
		mAns = new vector<char>;	// �� ���� ��ü ����
		mWords = new vector<Text>;
		mShorts = new vector<Text>;
		mLongs = new vector<Text>;
		sTextVectorLoaded = true;

		LoadTextFiles();			// ������ �ε��� ���Ϳ� �����մϴ�.
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


/* static ���� 5�� �ʱ�ȭ */
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

	else
	{
		cout << "Error | TypingManager::GetRandomText(const string& type)\n\n";
		exit(-1);
	}
}


double TypingManager::TypeSpeed() {
	/* ��� Ÿ�ڼӵ� ���ϴ� �Լ�
	���� ����(from Random) + �ʱ�ð�(from Timer) ���� �޾ƿ���
	���� �������� ������ �ش��ϴ� �ٿ� �ִ� ���� �о���� = ����
	�Է��ϴ� �������� ���� �ð� �޾ƿ���, �Է� Ÿ�� ++
	�ҿ�ð� = ����ð� - �ʱ�ð�
	��� Ÿ�ڼӵ� = �Է� Ÿ�� / �ҿ�ð�
	*/
	timetake = TimeTake();

	typeSpeed = typenum / timetake;
	return typeSpeed;
}

double TypingManager::TypeAccuracy() {
	/* ��Ȯ�� ��ȯ�ϴ� �Լ�
	������ string�� �ְ� ������ �� Ÿ���� �����Ѵ�.
	�Է� ������ ���� �Էµ��� string�� �ְ�
	���� ���Ѵ�.
	�齺���̽��� ���� �Է� Ÿ�� --
	�� �ܿ��� ���� ++
	���� ���ؼ� ���� ���ڵ��� ���� ������ ���� ���� �� cnt
	*/
	typeaccuracy = 100 * (double)(answer_cnt - correct_cnt) / answer_cnt;
	return typeaccuracy;
}

double TypingManager::TimeTake() {
	/* �ҿ�ð� üũ
	ù �Է½ð��� �޾Ƽ� ����ð����� ����.
	*/
	timetake = presentTime - startTime;
	return timetake; // ������ ������ ���� �ӽ÷� �߰��߽��ϴ�.
}

void TypingManager::setAns() {
	int cnt = 0;
	Timer time;
	while (1) {

		ans = _getch();
		if (cnt == 0) {
			time.Reset();
			startTime = time.GetElapsedTime();
			cnt++;
		}
		presentTime = time.GetElapsedTime();
		mAns->push_back(ans);
		if (sInstance->ans=='\b') {	//�齺���̽� �Է½� �ϴ� ���ǽ� ��� ��.
			mAns->pop_back();
			continue;
			/*
			mAns�� ��Ұ� ���� �� -> if�� ���ǽĿ� �߰��ϸ� �� ��.
			mAns�� ���� �ؽ�Ʈ�� ������ �� IsCorrect���� ���� ������ �־�� �ϰ�
			���� �����ε��� �����ٸ� correct_cnt�� ������ ����.
			*/
		}

		typenum++;
		typeSpeed = TypeSpeed();

		if (ans=='\n') {
			for (int i = 0; i < mAns->size; i++) {
				if (IsCorrect() == false) {
					//���ڻ� ���������� �ٲٱ�

					//�ٲ����� �־��ش�.
					mAns[i] = mAns[i];
				}
				else {
					correct_cnt++;
				}
			}
			typeaccuracy = TypeAccuracy();
			break;
		}
	}
}


bool TypingManager::IsCorrect() {
	//�Է¹��� ans�� �ؽ�Ʈ ���Ͽ� ���� ���� Ʋ�ȴ��� �¾Ҵ��� üũ�� �ϴ� �κ��Դϴ�.
	//�ؽ�Ʈ�� char Ÿ���� ���͸� ���� ���ؾ���.
	

	return true; // ������ ������ ���� �ӽ÷� �߰��߽��ϴ�.
}


TypingManager* TypingManager::sInstance = nullptr;

TypingManager* TypingManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new TypingManager;
	}

	return sInstance;
}

void TypingManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}