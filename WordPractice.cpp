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
	while (cnt==20) {	//������ ��� Ǯ�� �𸣴�

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

	cout << "Ÿ�ڼӵ�: " << typeSpeed << endl;
	cout << "��Ȯ��: " << typeaccuracy << endl;
	
	//���â�� ������ �Ѱ��ֱ�
	mInstance->setInfo(sInstance);
}