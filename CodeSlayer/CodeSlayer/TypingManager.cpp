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

	else
	{
		cout << "Error | TypingManager::GetRandomText(const string& type)\n\n";
		exit(-1);
	}
}


double TypingManager::TypeSpeed() {
	/* 평균 타자속도 구하는 함수
	난수 생성(from Random) + 초기시각(from Timer) 정보 받아오기
	문제 모음에서 난수에 해당하는 줄에 있는 정보 읽어오기 = 문제
	입력하는 순간마다 현재 시각 받아오기, 입력 타수 ++
	소요시간 = 현재시각 - 초기시각
	평균 타자속도 = 입력 타수 / 소요시간
	*/
	sInstance->timetake = sInstance->TimeTake();

	sInstance->typeSpeed = sInstance->typenum / sInstance->timetake;
	return sInstance->typeSpeed;
}

double TypingManager::TypeAccuracy() {
	/* 정확도 반환하는 함수
	문제를 string에 넣고 정답의 총 타수를 저장한다.
	입력 시작한 다음 입력들을 string에 넣고
	서로 비교한다.
	백스페이스가 들어가면 입력 타수 --
	그 외에는 전부 ++
	만약 비교해서 맞은 문자들이 있을 때마다 맞은 글자 수 cnt
	*/
	sInstance->typeaccuracy = 100 * ((double)sInstance->answer_cnt - sInstance->correct_cnt) / sInstance->answer_cnt;
	return sInstance->typeaccuracy;
}

double TypingManager::TimeTake() {
	/* 소요시간 체크
	첫 입력시간을 받아서 현재시간에서 빼줌.
	*/
	sInstance->timetake = time(0) - sInstance->startTime;
	return sInstance->timetake; // 컴파일 오류가 나서 임시로 추가했습니다.
}

void TypingManager::setAns() {
	int cnt = 0;
	while (1) {

		cin >> ans;
		if (cnt == 0) {
			startTime = (double)time(0);
			cnt++;
		}

		typenum++;
		typeSpeed = TypeSpeed();

		if (sInstance->ans == '\b') {	//백스페이스 입력시 일단 조건식 고려 중.
			mAns->pop_back();
			continue;
			/*
			mAns의 요소가 없을 때 -> if의 조건식에 추가하면 될 듯.
			mAns를 정답 텍스트와 비교해줄 때 IsCorrect에서 값의 변동도 있어야 하고
			만약 정답인데도 지웠다면 correct_cnt도 변동이 생김.
			*/
		}

		if (1) {	//단어, 짧은 글이면 마지막 엔터('\n'), 긴글까지 포함할 수 있는 종료조건이 필요.
			typeaccuracy = TypeAccuracy();
			/*이제 여기서 반환해야 할 데이터 타입들 중
			타자속도와 정확도를 짧은 글이면 짧은 글 객체 생성 후에 거기에
			전달하고 단어면 단어 긴글이면 긴글에 반환해주면 됩니다.
			통계창 구성이 될지 안 될지는 모르겠지만 일단 그 데이터 넘겨주면 됩니다.
			*/

			// 정확도, 타자 속도 출력해주면됩니다. 화면 전환이 필요할 듯 보입니다.

			//데이터를 넘겨준 후
			Release();
			this->~TypingManager();
			break;
		}
		mAns->push_back(ans);
		if (IsCorrect() == false) {
			//글자색 빨간색으로 바꾸기
		}
		else {
			correct_cnt++;
		}

	}
}


bool TypingManager::IsCorrect() {
	//입력받은 ans이 텍스트 파일에 들어가기 전에 틀렸는지 맞았는지 체크를 하는 부분입니다.
	//텍스트와 char 타입의 벡터를 서로 비교해야함.

	return true; // 컴파일 오류가 나서 임시로 추가했습니다.
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