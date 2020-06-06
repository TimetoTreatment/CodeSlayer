#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include "Console.h"
#include "Keyboard.h"

using namespace std;

class Statistics
{

private:

	Console *mConsole;
	Keyboard *mKeyboard;

	vector<int> mLongAccuracy;
	vector<int> mLongSpeed;

	vector<int> mWordAccuracy;
	vector<int> mWordSpeed;

	vector<int> mShortAccuracy;
	vector<int> mShortSpeed;

	int mAverageSpeed;
	int mAverageAccuarcy;

	const int mLeftRecordTableStartX = 9;
	const int mLeftRecordTableStartY = 17;
	const int mRightRecordTableStartX = 60;
	const int mRightRecordTableStartY = 17;

	const int mLeftAverageTableStartX = 13;
	const int mLeftAverageTableStartY = 26;
	const int mRightAverageTableStartX = 64;
	const int mRightAverageTableStartY = 26;

	const int mRecordTableStartToInputIntervalX = 11;
	const int mAverageTableStartToInputIntervalX = 12;

	const int mRecordTableIntervalX = 6;
	const int mRecordTableIntervalY = 2;

	const int mAverageTableIntervalX = 8;
	const int mAverageTableIntervalY = 2;

public:

	/* 메인 함수 */
	void Main();

	/* 파일 불러오기 함수 */
	void LoadStatistics();

	/* 평균 구하기 함수 */
	int ReturnAverage(const string& texttype,const string& object);

	/* 데이터 출력 함수*/


	/* 콘솔창 */
	void RenderStatistics();


	/* 생성자, 소멸자 */
	Statistics();
	


private:
	static Statistics* sInstance;

public:
	static Statistics* Instance();
	static void Release();
};

