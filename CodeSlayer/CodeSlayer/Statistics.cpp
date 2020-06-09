#include "Statistics.h"


Statistics::Statistics() {
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();

	mAverageSpeed = 0;
	mAverageAccuarcy = 0;
}


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

	// 정확도 저장

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

	// speed 저장

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

int Statistics::ReturnAverage(const string& texttype, const string& object) {

	int sum = 0, tmplen;

	if (object == "speed") {
		if (texttype == "word") {
			tmplen = mWordSpeed.size();
			for (int i = 0; tmplen > i; i++) {
				sum += mWordSpeed.at(i);
			}
			sum /= mWordSpeed.size(); // avg 구하기 위해 개수로 나누었음
		}
		else if (texttype == "short") {
			tmplen = mShortSpeed.size();
			for (int i = 0; tmplen > i; i++) {
				sum += mShortSpeed.at(i);
			}
			sum /= mShortSpeed.size();
		}
		else if (texttype == "long") {
			tmplen = mLongSpeed.size();
			for (int i = 0; tmplen > i; i++) {
				sum += mLongSpeed.at(i);
			}
			sum /= mLongSpeed.size();
		}

	}
	else if (object == "accuracy") {
		if (texttype == "word") {
			tmplen = mWordAccuracy.size();
			for (int i = 0; tmplen > i; i++) {
				sum += mWordAccuracy.at(i);
			}
			sum /= mWordAccuracy.size();
		}
		else if (texttype == "short") {
			tmplen = mShortAccuracy.size();
			for (int i = 0; tmplen > i; i++) {
				sum += mShortAccuracy.at(i);
			}
			sum /= mShortSpeed.size();
		}
		else if (texttype == "long") {
			tmplen = mLongAccuracy.size();
			for (int i = 0; tmplen > i; i++) {
				sum += mLongAccuracy.at(i);
			}
			sum /= mLongSpeed.size();
		}
	}

	return sum;
}


void Statistics::RecordEffect(int* text, int index)
{
	if (*text == *(text - 1) || index == 0) {
		mConsole->Color("white");
	}
	else if (*text > * (text - 1)) {
		mConsole->Color("green");
	}
	else {
		mConsole->Color("red");
	}
}


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

	int tmplen = 0;

	/*1~5 출력*/
	/*leftTable 타수 출력*/

	tmplen = mWordSpeed.size();
	for (int i = 0; tmplen > i; i++) {
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mLeftRecordTableStartY + mRecordTableIntervalY);
		RecordEffect(&mWordSpeed[i], i);
		cout << mWordSpeed[i];
	}

	tmplen = mShortSpeed.size();
	for (int i = 0; tmplen > i; i++) {
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mLeftRecordTableStartY + mRecordTableIntervalY * 2);
		RecordEffect(&mShortSpeed[i], i);
		cout << mShortSpeed[i];
	}

	tmplen = mLongSpeed.size();
	for (int i = 0; tmplen > i; i++) {
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mLeftRecordTableStartY + mRecordTableIntervalY * 3);
		RecordEffect(&mLongSpeed[i], i);
		cout << mLongSpeed[i];
	}

	/*rightTable 정확도 출력*/

	tmplen = mWordAccuracy.size();
	for (int i = 0; tmplen > i; i++) {
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mRightRecordTableStartY + mRecordTableIntervalY);
		RecordEffect(&mWordAccuracy[i], i);
		cout << mWordAccuracy[i];
	}

	tmplen = mShortAccuracy.size();
	for (int i = 0; tmplen > i; i++) {
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mRightRecordTableStartY + mRecordTableIntervalY * 2);
		RecordEffect(&mShortAccuracy[i], i);
		cout << mShortAccuracy[i];
	}

	tmplen = mLongAccuracy.size();
	for (int i = 0; tmplen > i; i++) {
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mRightRecordTableStartY + mRecordTableIntervalY * 3);
		RecordEffect(&mLongAccuracy[i], i);
		cout << mLongAccuracy[i];
	}

	/*각 평균 출력*/
	/*left 타수*/
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


	/*right 정확도*/
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


	for (;;) {
		mConsole->Draw("* Press Enter to Return *", "white", 51, 40);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter")) break;

		mConsole->Draw("* Press Enter to Return *", "yellow", 51, 40);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter")) break;
	}

}


void Statistics::Main()
{
	LoadStatistics();
	RenderStatistics();
}


Statistics* Statistics::sInstance = nullptr;

Statistics* Statistics::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Statistics;
	}
	return sInstance;
}

void Statistics::Release() {
	delete sInstance;
	sInstance = nullptr;
}
