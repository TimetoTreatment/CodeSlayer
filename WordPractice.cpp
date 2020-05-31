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
	mInstance->Instance();
	int cnt = 0;
	while (cnt==20) {	//문제를 몇번 풀지 모르니

		Text mShort = GetRandomText("word");

		cout << " * Random Word  : " << mShort.GetText() << "\n\n";

		setAns();
		cnt++;

		typeSpeed += TypeSpeed();
		typeaccuracy += TypeAccuracy();

		typeSpeed /= cnt;
		typeaccuracy /= cnt;

		cout << "타자속도: " << typeSpeed << endl;
		cout << "정확도: " << typeaccuracy << endl;

	}

	cout << "타자속도: " << typeSpeed << endl;
	cout << "정확도: " << typeaccuracy << endl;
	
	//통계창에 데이터 넘겨주기
	mInstance->setInfo(sInstance);
}