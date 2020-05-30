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
   while (1) {   //문제를 몇번 풀지 모르니

	  Text mShort = GetRandomText("word");
	  cout << " * Random Word  : " << mShort.GetText() << "\n\n";

	  while (1) {//줄 수만큼 반복 조건식을 바꿔줄 예정. 출력도 여기서 하면 안될 거 같은데 일단은 안까먹게 써뒀습니다.
		 setAns();
		 cnt++;
		 typeSpeed += TypeSpeed();
		 typeaccuracy = TypeAccuracy();

		 typeSpeed /= cnt;
		 typeaccuracy /= cnt;

		 cout << "타자속도: " << typeSpeed << endl;
		 cout << "정확도: " << typeaccuracy << endl;
	  }
   }
}

*/