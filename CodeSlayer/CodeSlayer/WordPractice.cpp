#include "WordPractice.h"

WordPractice* WordPractice::sInstance = nullptr;

WordPractice* WordPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new WordPractice;
	}
	return sInstance;
}

void WordPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void WordPractice::Main() {

	Text mShort = GetRandomText("word");

	cout << " * Random Word  : " << mShort.GetText() << "\n\n";

	setAns();


	/*
	여기서 실행한다고 하니
	여기서 이 타이핑 매니저의 객체가 화면에 문항을 출력하고
	setAns()함수를 계속 호출하면서 진행.
	*/
}