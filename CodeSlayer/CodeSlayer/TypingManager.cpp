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
	/* ��� Ÿ�ڼӵ� ���ϴ� �Լ�
	���� ����(from Random) + �ʱ�ð�(from Timer) ���� �޾ƿ���
	���� �������� ������ �ش��ϴ� �ٿ� �ִ� ���� �о���� = ����
	�Է��ϴ� �������� ���� �ð� �޾ƿ���, �Է� Ÿ�� ++
	�ҿ�ð� = ����ð� - �ʱ�ð�
	��� Ÿ�ڼӵ� = �Է� Ÿ�� / �ҿ�ð�
	*/
	timetake = TimeTake();

	typeSpeed = typenum / timetake;
	return typeSpeed;
}

double TypingManager::TypeAccuracy() {
	/* ��Ȯ�� ��ȯ�ϴ� �Լ�
	������ string�� �ְ� ������ �� Ÿ���� �����Ѵ�.
	�Է� ������ ���� �Էµ��� string�� �ְ�
	���� ���Ѵ�.
	�齺���̽��� ���� �Է� Ÿ�� --
	�� �ܿ��� ���� ++
	���� ���ؼ� ���� ���ڵ��� ���� ������ ���� ���� �� cnt
	*/
	typeaccuracy = 100* (double)(answer_cnt-correct_cnt)/answer_cnt;
	return typeaccuracy;
}

double TypingManager::TimeTake() {
	/* �ҿ�ð� üũ
	���� ���� �ð��� �޾Ƽ� ����ð����� ����.
	*/
	
}

void TypingManager::setAns() {
	while (1) {
		scanf("%c", &ans);

		if (ans == '\n') {	//�������� �� ���� ����ε� �� �κ��� �� �����غ��ڽ��ϴ�.
			typeaccuracy = TypeAccuracy();
			/*���� ���⼭ ��ȯ�ؾ� �� ������ Ÿ�Ե� ��
			Ÿ�ڼӵ��� ��Ȯ���� ª�� ���̸� ª�� �� ��ü ���� �Ŀ� �ű⿡
			�����ϰ� �ܾ�� �ܾ� ����̸� ��ۿ� ��ȯ���ָ� �˴ϴ�.
			���â ������ ���� �� ������ �𸣰����� �ϴ� �� ������ �Ѱ��ָ� �˴ϴ�.
			*/

			// ��Ȯ��, Ÿ�� �ӵ� ������ָ�˴ϴ�. ȭ�� ��ȯ�� �ʿ��� �� ���Դϴ�.

			break;
		}
		Ans.push_back(ans);
		if (IsCorrect == false) {
			//���ڻ� ���������� �ٲٱ�
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
	//�Է¹��� ans�� �ؽ�Ʈ ���Ͽ� ���� ���� Ʋ�ȴ��� �¾Ҵ��� üũ�� �ϴ� �κ��Դϴ�.
}

void TypingManager:: InstanceMaker() {
	/*
	pracType ���� ���� � ��ü�� ���������� �����ϴ�.
	�� GetRandeomText() �Լ����� ���̴� Type�� ��� ������ �����ص� �� pracType�Դϴ�.

	������ �� TypingManager ��ü���� �ڽ� Ŭ������ �Լ��� ȣ���� �� �ִ����Դϴ�.
	�׷��� WordPractice, Short, Long ���� TypingManager�� ������ִ� �� ���ͳ׿�.
	*/
}