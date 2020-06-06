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

	/* ���� �Լ� */
	void Main();

	/* ���� �ҷ����� �Լ� */
	void LoadStatistics();

	/* ��� ���ϱ� �Լ� */
	int ReturnAverage(const string& texttype,const string& object);

	/* ������ ��� �Լ�*/


	/* �ܼ�â */
	void RenderStatistics();


	/* ������, �Ҹ��� */
	Statistics();
	


private:
	static Statistics* sInstance;

public:
	static Statistics* Instance();
	static void Release();
};

