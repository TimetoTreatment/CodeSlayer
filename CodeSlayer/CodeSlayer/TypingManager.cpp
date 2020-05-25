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

		for (longText.clear();!file.eof();)
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
	timetake = TimeTake();

	typeSpeed = typenum / timetake;
	return typeSpeed;
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
	typeaccuracy = 100 * ((double)answer_cnt - correct_cnt) / answer_cnt;
	return typeaccuracy;
}

double TypingManager::TimeTake() {
	/* 소요시간 체크
	난수 받은 시간을 받아서 현재시간에서 빼줌.
	*/

	return 0; // 컴파일 오류가 나서 임시로 추가했습니다.
}

void TypingManager::setAns() {
	while (1) {
		scanf("%c", &ans);

		if (ans == '\n') {	//문제점은 긴 글일 경우인데 이 부분은 좀 생각해보겠습니다.
			typeaccuracy = TypeAccuracy();
			/*이제 여기서 반환해야 할 데이터 타입들 중
			타자속도와 정확도를 짧은 글이면 짧은 글 객체 생성 후에 거기에
			전달하고 단어면 단어 긴글이면 긴글에 반환해주면 됩니다.
			통계창 구성이 될지 안 될지는 모르겠지만 일단 그 데이터 넘겨주면 됩니다.
			*/

			// 정확도, 타자 속도 출력해주면됩니다. 화면 전환이 필요할 듯 보입니다.

			break;
		}
		mAns->push_back(ans);
		if (IsCorrect() == false) {
			//글자색 빨간색으로 바꾸기
		}
		typenum++;
		typeSpeed = TypeSpeed();
	}
}


bool TypingManager::IsCorrect() {
	//입력받은 ans이 텍스트 파일에 들어가기 전에 틀렸는지 맞았는지 체크를 하는 부분입니다.

	return true; // 컴파일 오류가 나서 임시로 추가했습니다.
}

void TypingManager::InstanceMaker() {
	/*
	pracType 값에 따라서 어떤 객체를 생성할지가 나뉩니다.
	그 GetRandeomText() 함수에서 쓰이는 Type을 멤버 변수에 저장해둔 게 pracType입니다.
	문제는 이 TypingManager 객체에서 자식 클래스의 함수를 호출할 수 있느냐입니다.
	그래서 WordPractice, Short, Long 등을 TypingManager에 상속해주는 게 어떨까싶네요.
	*/

	// (윤) 헤더에 있는 설명 참고..
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