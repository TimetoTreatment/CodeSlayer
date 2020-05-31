#include "ShortPractice.h"

ShortPractice* ShortPractice::sInstance = nullptr;

ShortPractice* ShortPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ShortPractice;
	}
	return sInstance;
}

void ShortPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ShortPractice::Main() {
	int cnt = 0;
	while (cnt==10) {	//문제 10번 풀기 전까지 못 나간다 ㅅㄱ

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

	mInstance->setInfo(sInstance);
}