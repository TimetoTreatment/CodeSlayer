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
	���⼭ �����Ѵٰ� �ϴ�
	���⼭ �� Ÿ���� �Ŵ����� ��ü�� ȭ�鿡 ������ ����ϰ�
	setAns()�Լ��� ��� ȣ���ϸ鼭 ����.
	*/
}