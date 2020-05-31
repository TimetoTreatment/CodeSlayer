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
	while (cnt==10) {	//���� 10�� Ǯ�� ������ �� ������ ����

		Text mShort = GetRandomText("word");

		cout << " * Random Word  : " << mShort.GetText() << "\n\n";

		setAns();
		cnt++;

		typeSpeed += TypeSpeed();
		typeaccuracy += TypeAccuracy();
		typeSpeed /= cnt;
		typeaccuracy /= cnt;

		cout << "Ÿ�ڼӵ�: " << typeSpeed << endl;
		cout << "��Ȯ��: " << typeaccuracy << endl;

	}

	mInstance->setInfo(sInstance);
}