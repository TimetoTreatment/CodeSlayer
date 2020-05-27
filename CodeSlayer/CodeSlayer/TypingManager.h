#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Text.h"
#include "Config.h"
#include "Random.h"
#include "Timer.h"

using namespace std;

class TypingManager {

private:

	void LoadTextFiles();
	// readFile() -> LoadTextFiles();
	// readFile() 함수는 반드시 실행되어야 하므로, 생성자로 이동하였습니다.


public:	// 테스트를 위해 임시로 public으로 하였습니다. 추후 변경 예정

	TypingManager();
	~TypingManager();

	static vector<char>* mAns;
	static vector<Text>* mWords;	// 스태틱 벡터 포인터입니다.
	static vector<Text>* mShorts;	// 모든 파생 클래스에서 하나의 벡터를 가리키기 위해 이렇게 만들었습니다.
	static vector<Text>* mLongs;
	static bool sTextVectorLoaded;
	// 저는 클래스 멤버 변수에 m을 붙여서 표기합니다. 지역 변수와 쉽게 구분이 가능합니다.
	// 로딩은 한 번만 이루어지면 되므로, 체크 변수를 만들었습니다.

	/*

	type 1 = word
	type 2 = short	// 숫자 대신, 직관성을 위해 문자열을 사용합니다.
	type 3 = long	// GetRandomText(1) 대신 GetRandomText("word")와 같이 사용합니다.

	*/

	int mRandomIndex;		// GetRandomText 함수에서 사용합니다.s
	double startTime;		// 각 문항에 대한 답안을 입력하기 시작한 시각을 담아둡니다.
	double typeSpeed;		// 타자 속도
	double typeaccuracy;	// 타자 정확도
	double timetake;		// 소요시간
	int correct_cnt;		// 맞은 타수의 갯수
	int answer_cnt;			// 정답의 총 타수
	int typenum;
	char ans;				// 문자 입력받기
	int pracType;

	//파일관련
	Text GetRandomText(const string& type);	// 직관성을 위해 문자열을 사용합니다.
											// 호출할 때, 숫자 대신 "word" 등을 사용합니다.

	//구하고 반환하는 기능을 합쳐놓은 함수.
	double TypeSpeed();		// 평균 타자 속도
	double TypeAccuracy();	// 타자 정확도
	double TimeTake();		// 소요 시간

	//setter
	void setAns();	//답안 문자 입력

	//채점 기능
	bool IsCorrect();

	//객체 만들기


private:
	static TypingManager* sInstance;

public:
	static TypingManager* Instance();
	static void Release();

	//연습 유형에 따른 객체 생성
	void InstanceMaker();

	/* (윤)

		TypingManager는 각 Practice에서 사용하는 기능 또는 변수의 집합이라고 생각하면 될 것 같습니다.
		그 자체로는 존재 또는 기능하지 않습니다. 변수, 기능을 각 클래스에 물려주기 위해 존재합니다.

		각 Practice는 그 자체로 독립적인 기능을 합니다.
		각 Practice 객체를 ProgramMain에서 생성한 후, 해당 객체의 main() 함수를 호출하여 사용하려고 합니다.

		요약
		  - WordPractice 등의 파생 클래스가, 메인에서 굴릴 객체입니다.
		  - TypingManager는 세(네) 파생 클래스에서 사용하는 변수와 기능을 제공할 뿐, 그 자체로는 존재하지 않습니다.
	*/
};