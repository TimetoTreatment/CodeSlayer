#include "Statistics.h"


Statistics::Statistics()
{
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();
}


///////////////
/* 파일 읽기 */
///////////////
void Statistics::LoadStatistics()
{
	int tmp;
	fstream file;

	mWordAccuracy.clear();
	mWordSpeed.clear();
	mShortAccuracy.clear();
	mShortSpeed.clear();
	mLongAccuracy.clear();
	mLongSpeed.clear();

	/* 정확도 저장 */
	file.open("Assets/statistics/wordaccuracy.txt");

	if (file.good()) {

		while (!file.eof()) {
			file >> tmp;

			mWordAccuracy.push_back(tmp);
		}
	}
	file.close();
	file.open("Assets/statistics/shortaccuracy.txt");

	if (file.good()) {

		while (!file.eof()) {
			file >> tmp;

			mShortAccuracy.push_back(tmp);
		}
	}
	file.close();
	file.open("Assets/statistics/longaccuracy.txt");

	if (file.good()) {

		while (!file.eof()) {
			file >> tmp;

			mLongAccuracy.push_back(tmp);
		}
	}
	file.close();

	/* 속도 저장 */
	file.open("Assets/statistics/wordspeed.txt");

	if (file.good()) {

		while (!file.eof()) {
			file >> tmp;

			mWordSpeed.push_back(tmp);
		}
	}
	file.close();
	file.open("Assets/statistics/shortspeed.txt");

	if (file.good()) {

		while (!file.eof()) {
			file >> tmp;

			mShortSpeed.push_back(tmp);
		}
	}
	file.close();
	file.open("Assets/statistics/longspeed.txt");

	if (file.good()) {

		while (!file.eof()) {
			file >> tmp;

			mLongSpeed.push_back(tmp);
		}
	}
	file.close();
}


///////////////
/* 평균 계산 */
///////////////
int Statistics::ReturnAverage(const string& textType, const string& object) {

	int i;
	int sum = 0, tmplen;

	if (object == "speed") {
		if (textType == "word") {
			tmplen = mWordSpeed.size();
			for (i = 0; tmplen > i; i++) {
				sum += mWordSpeed.at(i);
			}
			sum /= mWordSpeed.size(); // avg 구하기 위해 개수로 나누었음
		}
		else if (textType == "short") {
			tmplen = mShortSpeed.size();
			for (i = 0; tmplen > i; i++) {
				sum += mShortSpeed.at(i);
			}
			sum /= mShortSpeed.size();
		}
		else if (textType == "long") {
			tmplen = mLongSpeed.size();
			for (i = 0; tmplen > i; i++) {
				sum += mLongSpeed.at(i);
			}
			sum /= mLongSpeed.size();
		}

	}
	else if (object == "accuracy") {
		if (textType == "word") {
			tmplen = mWordAccuracy.size();
			for (i = 0; tmplen > i; i++) {
				sum += mWordAccuracy.at(i);
			}
			sum /= mWordAccuracy.size();
		}
		else if (textType == "short") {
			tmplen = mShortAccuracy.size();
			for (i = 0; tmplen > i; i++) {
				sum += mShortAccuracy.at(i);
			}
			sum /= mShortSpeed.size();
		}
		else if (textType == "long") {
			tmplen = mLongAccuracy.size();
			for (i = 0; tmplen > i; i++) {
				sum += mLongAccuracy.at(i);
			}
			sum /= mLongSpeed.size();
		}
	}

	return sum;
}


////////////////////
/* 기록 색상 효과 */
////////////////////
void Statistics::RecordEffect(const vector<int>& value, int index)
{
	if (index == 0)
	{
		mConsole->Color("white");
		return;
	}

	if (value[index - 1] == value[index])
		mConsole->Color("white");

	else if (value[index - 1] < value[index])
		mConsole->Color("green");

	else
		mConsole->Color("red");
}


///////////////
/* 통계 출력 */
///////////////
void Statistics::RenderStatistics()
{
	mConsole->Draw("Assets/layout/statistics_main.txt", "white", 0, 2);
	mConsole->Draw("Assets/layout/statistics_recordtable.txt", "white", mLeftRecordTableStartX, mLeftRecordTableStartY);
	mConsole->Draw("Assets/layout/statistics_recordtable.txt", "white", mRightRecordTableStartX, mRightRecordTableStartY);

	mConsole->Draw("Assets/layout/statistics_averagetable.txt", "white", mLeftAverageTableStartX, mLeftAverageTableStartY);
	mConsole->Draw("Assets/layout/statistics_averagetable.txt", "white", mRightAverageTableStartX, mRightAverageTableStartY);

	int wordSpeedAverage = 0;
	int shortSpeedAverage = 0;
	int longSpeedAverage = 0;

	size_t index;

	/* 속도 표 출력*/
	for (index = 0; index < mWordSpeed.size(); index++)
	{
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * index, mLeftRecordTableStartY + mRecordTableIntervalY);
		RecordEffect(mWordSpeed, index);
		cout << mWordSpeed[index];
	}

	for (index = 0; index < mShortSpeed.size(); index++)
	{
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * index, mLeftRecordTableStartY + mRecordTableIntervalY * 2);
		RecordEffect(mShortSpeed, index);
		cout << mShortSpeed[index];
	}

	for (index = 0; index < mLongSpeed.size(); index++)
	{
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * index, mLeftRecordTableStartY + mRecordTableIntervalY * 3);
		RecordEffect(mLongSpeed, index);
		cout << mLongSpeed[index];
	}

	/* 정확도 표 출력*/
	for (index = 0; index < mWordAccuracy.size(); index++)
	{
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * index, mRightRecordTableStartY + mRecordTableIntervalY);
		RecordEffect(mWordAccuracy, index);
		cout << mWordAccuracy[index];
	}

	for (index = 0; index < mShortAccuracy.size(); index++)
	{
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * index, mRightRecordTableStartY + mRecordTableIntervalY * 2);
		RecordEffect(mShortAccuracy, index);
		cout << mShortAccuracy[index];
	}

	for (index = 0; index < mLongAccuracy.size(); index++)
	{
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * index, mRightRecordTableStartY + mRecordTableIntervalY * 3);
		RecordEffect(mLongAccuracy, index);
		cout << mLongAccuracy[index];
	}

	/* 평균 속도 출력 */
	mConsole->Color("red");
	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX - 1, mLeftAverageTableStartY);
	cout << "Word";
	mConsole->Color("white");
	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX, mLeftAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("word", "speed");

	mConsole->Color("green");
	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX - 1, mLeftAverageTableStartY);
	cout << "Short";
	mConsole->Color("white");
	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX, mLeftAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("short", "speed");

	mConsole->Color("yellow");
	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX * 2 - 1, mLeftAverageTableStartY);
	cout << "Long";
	mConsole->Color("white");
	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX * 2, mLeftAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("long", "speed");


	/* 평균 정확도 출력 */
	mConsole->Color("red");
	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX - 1, mRightAverageTableStartY);
	cout << "Word";
	mConsole->Color("white");
	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX, mRightAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("word", "accuracy");

	mConsole->Color("green");
	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX - 1, mRightAverageTableStartY);
	cout << "Short";
	mConsole->Color("white");
	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX, mRightAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("short", "accuracy");

	mConsole->Color("yellow");
	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX * 2 - 1, mRightAverageTableStartY);
	cout << "Long";
	mConsole->Color("white");
	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX * 2, mRightAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("long", "accuracy");


	for (;;)
	{
		mConsole->Draw("* Press Enter to Return *", "white", 51, 40);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;

		mConsole->Draw("* Press Enter to Return *", "yellow", 51, 40);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}
}


//////////
/* 메인 */
//////////
void Statistics::Main()
{
	LoadStatistics();	// 파일 읽기
	RenderStatistics();	// 통계 출력
}


Statistics* Statistics::sInstance = nullptr;

Statistics* Statistics::Instance()
{
	if (sInstance == nullptr)
		sInstance = new Statistics;

	return sInstance;
}

void Statistics::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
