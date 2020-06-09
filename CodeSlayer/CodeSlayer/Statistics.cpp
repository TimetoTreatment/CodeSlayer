#include "Statistics.h"


Statistics::Statistics() {
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();
}




void Statistics::LoadStatistics() {

	fstream file;

	// 정확도 저장

	file.open("Assets/statistics/wordaccuracy.txt");


	int tmp;
	
	if (file.is_open()) {

		while (!file.eof()) {
			file >> tmp;
			
			mWordAccuracy.push_back(tmp);
		}
	}

	file.close();

	file.open("Assets/statistics/shortaccuracy.txt");


	if (file.is_open()) {

		while (!file.eof()) {
			file >> tmp;

			mShortAccuracy.push_back(tmp);
		}
	}
	file.close();

	file.open("Assets/statistics/longaccuracy.txt");

	
	if (file.is_open()) {

		while (!file.eof()) {
			file >> tmp;
			
			mLongAccuracy.push_back(tmp);
		}
	}
	file.close();

	
	// speed 저장

	file.open("Assets/statistics/wordspeed.txt");


	if (file.is_open()) {

		while (!file.eof()) {
			file >> tmp;

			mWordSpeed.push_back(tmp);
		}
	}

	file.close();

	file.open("Assets/statistics/shortspeed.txt");

	if (file.is_open()) {

		while (!file.eof()) {
			file >> tmp;

			mShortSpeed.push_back(tmp);
		}
	}

	file.close();

	file.open("Assets/statistics/longspeed.txt");

	
	if (file.is_open()) {

		while (!file.eof()) {
			file >> tmp;

			mLongSpeed.push_back(tmp);
		}
	}

	file.close();

}

int Statistics::ReturnAverage(const string& texttype,const string& object ) {

	int sum = 0,tmplen;

	if (object == "speed") {
		if (texttype == "word") {
			tmplen = mWordSpeed.size();
			for (int i = 0;tmplen > i;i++) {
				sum += mWordSpeed.at(i);
			}
			sum /= mWordSpeed.size(); // avg 구하기 위해 개수로 나누었음
		}
		else if (texttype == "short") {
			tmplen = mShortSpeed.size();
			for (int i = 0;tmplen > i;i++) {
				sum += mShortSpeed.at(i);
			}
			sum /= mShortSpeed.size();
		}
		else if (texttype == "long") {
			tmplen = mLongSpeed.size();
			for (int i = 0;tmplen > i;i++) {
				sum += mLongSpeed.at(i);
			}
			sum /= mLongSpeed.size();
		}

	}
	else if (object == "accuracy") {
		if (texttype == "word") {
			tmplen = mWordAccuracy.size();
			for (int i = 0;tmplen > i;i++) {
				sum += mWordAccuracy.at(i);
			}
			sum /= mWordAccuracy.size();
		}
		else if (texttype == "short") {
			tmplen = mShortAccuracy.size();
			for (int i = 0;tmplen > i;i++) {
				sum += mShortAccuracy.at(i);
			}
			sum /= mShortSpeed.size();
		}
		else if (texttype == "long") {
			tmplen = mLongAccuracy.size();
			for (int i = 0;tmplen > i;i++) {
				sum += mLongAccuracy.at(i);
			}
			sum /= mLongSpeed.size();
		}
	}

	return sum;
}



void Statistics::RenderStatistics()
{
	mConsole->Draw("Assets/layout/statistics_main.txt", "white", 9, 5);
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

	tmplen = mLongSpeed.size();
	for (int i = 0;tmplen > i;i++) {
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mLeftRecordTableStartY + mRecordTableIntervalY);
		cout << mLongSpeed[i];
	}

	tmplen = mShortSpeed.size();
	for (int i = 0;tmplen > i;i++) {
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mLeftRecordTableStartY + mRecordTableIntervalY * 2);
		cout << mShortSpeed[i];
	}

	tmplen = mWordSpeed.size();
	for (int i = 0;tmplen > i;i++) {
		mConsole->CursorPosition(mLeftRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mLeftRecordTableStartY + mRecordTableIntervalY * 3);
		cout << mWordSpeed[i];
	}

	/*rightTable 정확도 출력*/

	tmplen = mLongAccuracy.size();
	for (int i = 0;tmplen > i;i++) {
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mRightRecordTableStartY + mRecordTableIntervalY);
		cout << mLongAccuracy[i];
	}

	tmplen = mShortAccuracy.size();
	for (int i = 0;tmplen > i;i++) {
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mRightRecordTableStartY + mRecordTableIntervalY * 2);
		cout << mShortAccuracy[i];
	}

	tmplen = mWordAccuracy.size();
	for (int i = 0;tmplen > i;i++) {
		mConsole->CursorPosition(mRightRecordTableStartX + mRecordTableStartToInputIntervalX + mRecordTableIntervalX * i, mRightRecordTableStartY + mRecordTableIntervalY * 3);
		cout << mWordAccuracy[i];
	}

	/*각 평균 출력*/
	/*left 타수*/
	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX , mLeftAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("long", "speed");

	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX, mLeftAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("short", "speed");

	mConsole->CursorPosition(mLeftAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX * 2, mLeftAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("word", "speed");
	

	/*right 정확도*/
	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX, mRightAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("long", "accuracy");

	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX, mRightAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("short", "accuracy");

	mConsole->CursorPosition(mRightAverageTableStartX + mAverageTableStartToInputIntervalX + mAverageTableIntervalX * 2, mRightAverageTableStartY + mAverageTableIntervalY);
	cout << ReturnAverage("word", "accuracy");


	for (;;) {
		mConsole->Draw("* Press Enter to Return *", "white", 51, 39);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter")) break;

		mConsole->Draw("* Press Enter to Return *", "yellow", 51, 39);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter")) break;
	}

}



void Statistics::Main()
{
	system("mode con lines=45 cols=130 ");
	
	LoadStatistics();
	RenderStatistics();

	mConsole->Clear();
	mKeyboard->Clear();

	
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


