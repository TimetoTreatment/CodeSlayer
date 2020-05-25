#include "TypingManager.h"


Text TypingManager::GetRandomText(int type) {
	/*
	type 1 = word
	type 2 = short
	type 3 = long
	*/
	int ran;
	pracType = type;

	if (type == 1) {
		ran = Random::Integer(0, FileNum::Word - 1);

		while (Words[ran].GetIsUsed())
			ran = Random::Integer(0, FileNum::Word - 1);

		Words[ran].IsUsed();

		return Words[ran];
	}
	else if (type == 2) {
		ran = Random::Integer(1, FileNum::Short);

		if ((sInstance->Shorts).at(ran).GetIsUsed()) {
			(sInstance->Shorts).at(ran).IsUsed();
			return (sInstance->Shorts).at(ran);
		}
		else {
			return sInstance->GetRandomText(2);
		}
	}
	else if (type == 3) {
		ran = Random::Integer(1, FileNum::Long);

		if ((sInstance->Longs).at(ran).GetIsUsed()) {
			(sInstance->Longs).at(ran).IsUsed();
			return (sInstance->Longs).at(ran);
		}
		else {
			return sInstance->GetRandomText(3);
		}
	}
}

void TypingManager::readFile() {

	ifstream txt;
	Text tmp;
	string str;

	txt.open("words.txt");
	if (txt.is_open()) {

		for (int i = 0; FileNum::Word > i; i++) {
			getline(txt, str);
			tmp.SetText(str);
			tmp.SetTextLength(str.length());
			Words.push_back(tmp);
		}

	}
	txt.close();

	txt.open("shorts.txt");
	if (txt.is_open()) {

		for (int i = 0; FileNum::Short > i; i++) {
			getline(txt, str);
			tmp.SetText(str);
			tmp.SetTextLength(str.length());
			(sInstance->Shorts).push_back(tmp);
		}
	}
	txt.close();

	string path = "long";
	for (int i = 0; FileNum::Long > i; i++) {
		str = path;
		str += i + '0';
		str += "txt";
		txt.open(str);
		if (txt.is_open()) {

			string tmpstr = "";

			while (!txt.eof()) {

				string temp;
				getline(txt, temp);
				tmpstr += temp;
				tmpstr += '\n';
			}

			tmp.SetText(tmpstr);
			tmp.SetTextLength(tmpstr.length());
			(sInstance->Longs).push_back(tmp);
		}
		txt.close();
	}
}

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

int TypingManager::TypeSpeed() {
	/* 평균 타자속도 구하는 함수
	난수 생성(from Random) + 초기시각(from Timer) 정보 받아오기
	문제 모음에서 난수에 해당하는 줄에 있는 정보 읽어오기 = 문제
	입력하는 순간마다 현재 시각 받아오기, 입력 타수 ++
	소요시간 = 현재시각 - 초기시각
	평균 타자속도 = 입력 타수 / 소요시간
	*/
	timetake = TimeTake();

	typeSpeed = typenum / timetake;
	return typeSpeed;
}

double TypingManager::TypeAccuracy() {
	/* 정확도 반환하는 함수
	문제를 string에 넣고 정답의 총 타수를 저장한다.
	입력 시작한 다음 입력들을 string에 넣고
	서로 비교한다.
	백스페이스가 들어가면 입력 타수 --
	그 외에는 전부 ++
	만약 비교해서 맞은 문자들이 있을 때마다 맞은 글자 수 cnt
	*/
	typeaccuracy = 100* (double)(answer_cnt-correct_cnt)/answer_cnt;
	return typeaccuracy;
}

double TypingManager::TimeTake() {
	/* 소요시간 체크
	난수 받은 시간을 받아서 현재시간에서 빼줌.
	*/
	
}

void TypingManager::setAns() {
	while (1) {
		scanf("%c", &ans);

		if (ans == '\n') {	//문제점은 긴 글일 경우인데 이 부분은 좀 생각해보겠습니다.
			typeaccuracy = TypeAccuracy();
			/*이제 여기서 반환해야 할 데이터 타입들 중
			타자속도와 정확도를 짧은 글이면 짧은 글 객체 생성 후에 거기에
			전달하고 단어면 단어 긴글이면 긴글에 반환해주면 됩니다.
			통계창 구성이 될지 안 될지는 모르겠지만 일단 그 데이터 넘겨주면 됩니다.
			*/

			// 정확도, 타자 속도 출력해주면됩니다. 화면 전환이 필요할 듯 보입니다.

			break;
		}
		Ans.push_back(ans);
		if (IsCorrect == false) {
			//글자색 빨간색으로 바꾸기
		}
		typenum++;
		typeSpeed = TypeSpeed();
	}
}

TypingManager* TypingManager::sInstance = nullptr;
TypingManager* TypingManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new TypingManager;
	}
	return sInstance;
}

void TypingManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

bool TypingManager::IsCorrect() {
	//입력받은 ans이 텍스트 파일에 들어가기 전에 틀렸는지 맞았는지 체크를 하는 부분입니다.
}

void TypingManager:: InstanceMaker() {
	/*
	pracType 값에 따라서 어떤 객체를 생성할지가 나뉩니다.
	그 GetRandeomText() 함수에서 쓰이는 Type을 멤버 변수에 저장해둔 게 pracType입니다.

	문제는 이 TypingManager 객체에서 자식 클래스의 함수를 호출할 수 있느냐입니다.
	그래서 WordPractice, Short, Long 등을 TypingManager에 상속해주는 게 어떨까싶네요.
	*/
}