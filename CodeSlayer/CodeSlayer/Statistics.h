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

	const int mLeftRecordTableStartX = 18;
	const int mLeftRecordTableStartY = 17;
	const int mRightRecordTableStartX = 69;
	const int mRightRecordTableStartY = 17;

	const int mLeftAverageTableStartX = 22;
	const int mLeftAverageTableStartY = 27;
	const int mRightAverageTableStartX = 74;
	const int mRightAverageTableStartY = 27;

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

	


	/* 콘솔창 */
	void RenderStatistics();

	/* 기록 이펙트 */
	void RecordEffect(int *text, int index);

	
	/* 생성자, 소멸자 */
	Statistics();
	


private:
	static Statistics* sInstance;

public:
	static Statistics* Instance();
	static void Release();
};

