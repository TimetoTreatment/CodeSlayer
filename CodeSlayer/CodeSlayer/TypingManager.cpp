#include "TypingManager.h"

////////////////////////
/* static 변수 초기화 */
////////////////////////
bool TypingManager::sTextVectorLoaded = false;

vector<Text>* TypingManager::mWords = nullptr;
vector<Text>* TypingManager::mShorts = nullptr;
vector<Text>* TypingManager::mLongs = nullptr;

vector<int>* TypingManager::mRandomTableWord = nullptr;
vector<int>* TypingManager::mRandomTableShort = nullptr;
vector<int>* TypingManager::mRandomTableLong = nullptr;


/////////////////////////////
/* 프리셋 텍스트 파일 로드 */
/////////////////////////////
void TypingManager::LoadTextFiles()
{
	int count;
	Text newText;
	string path;
	string line;
	string longText;
	fstream file;

	file.open("Assets/preset/word.txt");	// 단어 프리셋 텍스트 파일 열기

	for (count = 0; count < FileNum::Word; count++)	// 환경 변수에 정의된 "단어의 수" 만큼 반복
	{
		getline(file, line);						// 단어 한 개를 읽어

		newText.SetText(line);						// 텍스트 객체에 저장
		newText.SetTextLength(line.length());		// 텍스트 객체의 문자열 길이 지정

		mWords->emplace_back(newText);				// 단어 벡터에 텍스트 객체 저장
	}

	file.close();
	file.open("Assets/preset/short.txt");	// 짧은 글 프리셋 텍스트 파일 열기

	for (count = 0; count < FileNum::Short; count++)
	{
		getline(file, line);

		newText.SetText(line);
		newText.SetTextLength(line.length());

		mShorts->emplace_back(newText);
	}

	file.close();

	for (count = 0; count < FileNum::Long; count++)						// 환경 변수에 정의된 "긴 글의 수" 만큼 반복
	{
		path = "Assets/preset/long/long" + to_string(count) + ".txt";	// 각 파일의 경로로 설정

		file.open(path);							// 긴 글 프리셋 텍스트 파일 열기

		if (!file.good())							// 예외 처리
		{
			cout << "Cannot Open " << path;
			exit(-1);
		}

		for (longText.clear(); !file.eof();)		// 파일의 끝까지
		{
			getline(file, line);					// 한 줄 읽어
			longText += line + '\n';				// 긴 글 문자열에 추가
		}

		newText.SetText(longText);					// 텍스트 객체에 긴 글 문자열을 저장
		newText.SetTextLength(longText.length());	// 문자열의 길이 지정

		mLongs->emplace_back(newText);				// 긴 글 벡터에 텍스트 객체 저장
		file.close();								// 파일 닫기
	}
}


//////////////////////
/* 난수 테이블 생성 */
//////////////////////
void TypingManager::SetRandomTable(const string& type)
{
	int temp;
	int count;
	int shuffleCount;
	int randomIndex1;
	int randomIndex2;

	if (type == "word")						// 인자가 단어일 때
	{
		shuffleCount = FileNum::Word * 2;							// 프리셋 단어 수의 2배만큼 반복

		for (count = 0; count < shuffleCount; count++)				// 난수 테이블 뒤섞기 반복문
		{
			randomIndex1 = Random::Integer(0, FileNum::Word - 1);	// 무작위 인덱스 선택
			randomIndex2 = Random::Integer(0, FileNum::Word - 1);	// 무작위 인덱스 선택

			temp = mRandomTableWord->at(randomIndex1);				// 테이블 내 두 인덱스 스왑
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

	else	// 예외 처리
	{
		cout << "Error | TypingManager::SetRandomTable(const string& type)\n\n";
		exit(-1);
	}
}


/////////////////////////
/* 난수 테이블 값 반환 */
/////////////////////////
int TypingManager::GetRandomTableNum(const string& type)
{
	mRandomTableIndex++;	// 테이블 인덱스 증가
	
	if (type == "word")									// 인자가 단어일 때
	{
		if (mRandomTableIndex == FileNum::Word)			// 테이블의 마지막 난수까지 사용하였다면
		{
			SetRandomTable("word");						// 난수 테이블을 다시 생성
			mRandomTableIndex = 0;						// 인덱스 초기화
		}

		return mRandomTableWord->at(mRandomTableIndex);	// 테이블[인덱스] 반환 
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

	else	// 예외 처리
	{
		cout << "Error | TypingManager::GetRandomTableNum(const string& type)\n\n";
		exit(-1);
	}
}


////////////
/* 생성자 */
////////////
TypingManager::TypingManager()
{
	if (sTextVectorLoaded == false)				// 프리셋 텍스트 파일을 로드한 적이 없다면
	{
		sTextVectorLoaded = true;				// 플래그 업데이트

		mWords = new vector<Text>;				// 단어 벡터 생성
		mShorts = new vector<Text>;				// 짧은 글 벡터 생성
		mLongs = new vector<Text>;				// 긴 글 벡터 생성

		LoadTextFiles();						// 프리셋 텍스트 파일 로드

		mRandomTableWord = new vector<int>;		// 단어 난수 테이블 벡터 생성
		mRandomTableShort = new vector<int>;	// 짧은 글 난수 테이블 벡터 생성
		mRandomTableLong = new vector<int>;		// 긴 글 난수 테이블 벡터 생성

		int count;

		/* 테이블 초기화 */
		for (count = 0; count < FileNum::Word; count++)
			mRandomTableWord->emplace_back(count);		

		for (count = 0; count < FileNum::Short; count++)
			mRandomTableShort->emplace_back(count);

		for (count = 0; count < FileNum::Long; count++)
			mRandomTableLong->emplace_back(count);

		/* 난수 테이블 생성 */
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
/* 소멸자 */
////////////
TypingManager::~TypingManager()
{
	sTextVectorLoaded = false;

	delete mTimer;
	delete mWords;				// 벡터 삭제
	delete mShorts;				//
	delete mLongs;				//
	delete mRandomTableWord;	//
	delete mRandomTableShort;	//
	delete mRandomTableLong;	//

	mTimer = nullptr;
	mWords = nullptr;				// nullptr이 아니라면 
	mShorts = nullptr;				// 다음 파생 클래스가 소멸될 때
	mLongs = nullptr;				// delete에서 오류 발생
	mRandomTableWord = nullptr;		// 
	mRandomTableShort = nullptr;	//
	mRandomTableLong = nullptr;		//
}


///////////////////////////////
/* 무작위 프리셋 텍스트 반환 */
///////////////////////////////
Text TypingManager::GetRandomText(const string& type)
{
	if (type == "word")
		return mWords->at(GetRandomTableNum("word"));	// 단어[난수]의 텍스트 객체 반환

	else if (type == "short")
		return mShorts->at(GetRandomTableNum("short"));	// 짧은글[난수]의 텍스트 객체 반환

	else if (type == "long")
		return mLongs->at(GetRandomTableNum("long"));	// 긴글[난수]의 텍스트 객체 반환

	else
	{
		cout << "Error | TypingManager::GetRandomText(const string& type)\n\n";
		exit(-1);
	}
}
