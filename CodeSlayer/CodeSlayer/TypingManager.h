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


protected:

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

	int mRandomIndex;		// GetRandomText 함수에서 사용합니다.
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


	//객체 만들기

};