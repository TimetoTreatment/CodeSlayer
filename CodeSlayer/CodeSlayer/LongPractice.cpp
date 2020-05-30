#include "LongPractice.h"

LongPractice* LongPractice::sInstance = nullptr;

LongPractice* LongPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new LongPractice;
	}

	return sInstance;
}

void LongPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}


void LongPractice::Main()
{
	Text mShort = GetRandomText("word");
	cout << " * Random Word  : " << mShort.GetText() << "\n\n";



	




}

/*

void LongPractice::Main() {

   int cnt = 0;
   while (1) {   //������ ��� Ǯ�� �𸣴�

	  Text mShort = GetRandomText("word");
	  cout << " * Random Word  : " << mShort.GetText() << "\n\n";

	  while (1) {//�� ����ŭ �ݺ� ���ǽ��� �ٲ��� ����. ��µ� ���⼭ �ϸ� �ȵ� �� ������ �ϴ��� �ȱ�԰� ��׽��ϴ�.
		 setAns();
		 cnt++;
		 typeSpeed += TypeSpeed();
		 typeaccuracy = TypeAccuracy();

		 typeSpeed /= cnt;
		 typeaccuracy /= cnt;

		 cout << "Ÿ�ڼӵ�: " << typeSpeed << endl;
		 cout << "��Ȯ��: " << typeaccuracy << endl;
	  }
   }
}

*/