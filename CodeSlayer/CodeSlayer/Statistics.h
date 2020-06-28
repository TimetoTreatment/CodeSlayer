//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 통계
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 최근 5회의 타자 연습 기록 제공

	2. 기능
		- 타자 연습 기능별로 분류
		- 최근 5회의 정확도와 속도 출력
		- 이전보다 기록이 나아졌다면 초록색, 나빠졌다면 빨간색
*/

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

	Statistics();

	Console* mConsole;
	Keyboard* mKeyboard;

	vector<int> mWordAccuracy;
	vector<int> mWordSpeed;

	vector<int> mShortAccuracy;
	vector<int> mShortSpeed;

	vector<int> mLongAccuracy;
	vector<int> mLongSpeed;

	int mAverageSpeed = 0;
	int mAverageAccuarcy = 0;

	const int mLeftRecordTableStartX = 18;
	const int mLeftRecordTableStartY = 19;
	const int mRightRecordTableStartX = 69;
	const int mRightRecordTableStartY = 19;

	const int mLeftAverageTableStartX = 22;
	const int mLeftAverageTableStartY = 29;
	const int mRightAverageTableStartX = 74;
	const int mRightAverageTableStartY = 29;

	const int mRecordTableStartToInputIntervalX = 11;
	const int mAverageTableStartToInputIntervalX = 12;

	const int mRecordTableIntervalX = 6;
	const int mRecordTableIntervalY = 2;

	const int mAverageTableIntervalX = 8;
	const int mAverageTableIntervalY = 2;

	/* 파일 읽기 */
	void LoadStatistics();

	/* 평균 계산 */
	int ReturnAverage(const string& textType, const string& object);

	/* 기록 색상 효과 */
	void RecordEffect(const vector<int>& value , int index);

	/* 통계 출력 */
	void RenderStatistics();

public:

	/* 메인 */
	void Main();


private:
	static Statistics* sInstance;

public:
	static Statistics* Instance();
	static void Release();
};

