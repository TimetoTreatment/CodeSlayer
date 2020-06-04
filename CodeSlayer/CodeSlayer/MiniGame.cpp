#include"MiniGame.h"
//#include"console.h"
//#include "Random.h"
// -> ��� ���Ϸ� �Ű���ϴ�.

using namespace std;

void MiniGame::Main() {//������ ��ü���� �帧�� �����Ѵ�.
	char input;

	mConsole->Color("white");
	string Answer;
	int cnt = 0;

	int count;
	int len;
	string path;
	string line;
	string Game, GameAns;//Game�� �Է¹޴� �����̴�. GameAns�� ���� �����̴�.
	fstream file;

	int rand;
	rand = mRandom->Integer(0, 2);//���ڴ� �����Ѵ�. �̿ϼ��̱⿡ ���� ������ �������.

	//--------------------------������ �Է¹޴´�---------------------//
	path = "Assets/preset/Game/game" + to_string(rand) + ".txt";
	file.open(path);

	if (!file.is_open())
	{
		cout << "Cannot Open " << path;
		exit(-1);
	}

	for (Game.clear(); !file.eof();)
	{
		getline(file, line);
		Game += line + '\n';
	}
	file.close();
	//--------------------------���並 �Է¹޴´�---------------------//
	path = "Assets/preset/Game_Ans/gameAns" + to_string(rand) + ".txt";
	file.open(path);

	if (!file.is_open())
	{
		cout << "Cannot Open " << path;
		exit(-1);
	}

	for (GameAns.clear(); !file.eof();)
	{
		getline(file, line);
		GameAns += line;
	}
	file.close();

	//------------------------���� �Է��� �����Ѵ�.---------------------//


	int Answer_len = GameAns.length();
	int i = 0;
	for (i = 0; i < Answer_len; i++) {
		Answer += '_';
	}
	SetLife(Answer_len + 3);//������ ���̺��� ��ȸ�� 3�� �� �ش�.

	while (1) {
		mConsole->CursorPosition(5, 5);
		cout << Game << endl;
		mConsole->CursorPosition(95, 5);
		cout << "Life : " << GetLife() << endl;;//��� ���
		mConsole->CursorPosition(95, 7);
		cout << "Score : " << GetScore() << endl;;//���� ���
		mConsole->CursorPosition(85, 23);
		cout << Answer;
		mConsole->CursorPosition(45, 23);
		cout << "������� ��ĭ�� ���ڸ� �־��ּ��� ==>>";
		mConsole->CursorPosition(45, 26);
		cout << "�Է� : ";
		cin >> input;//�ش�ĭ�� ���ڸ� �ִ´�.
		//--------------------------------������------------------------------------------------//
		int j = 0;
		int Good = 0;
		for (j = 0; j < Answer_len; j++) {
			if (IsCorrect(input, GameAns[j], &Answer[j]) == true) {
				Answer[j] = input;
				cnt++;
				Good = 1;
			}
		}
		if (Good == 1) {
			mConsole->CursorPosition(60, 26);
			cout << "\"Good\"";
		}
		else {
			SetLife();//����� �پ���.
			mConsole->CursorPosition(60, 26);
			cout << "\"Bad\"";
		}
		draw_man();
		//-------------------------------------------------------------------------------------//
		if (cnt == Answer_len) {
			break;
		}
		if (GetLife() == 0) {
			break;
		}
	}
	if (cnt == Answer_len) {
		mConsole->Clear();
		mConsole->CursorPosition(45, 23);
		cout << "���� ���� ==>>";
		mConsole->CursorPosition(60, 23);
		cout << Answer;
		mConsole->CursorPosition(45, 25);
		cout << "������ �� �־����ϴ�.";
	}
	if (GetLife() == 0) {
		mConsole->Clear();
		draw_man();
		mConsole->CursorPosition(45, 25);
		cout << " �����Ͽ����ϴ�. ";
	}
	mConsole->Draw("Press the Enter to Continue.", "white", 45, 30);

	for (;;)
	{
		mKeyboard->StaticInput();
	
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear();
}
//����ڰ� �Է��� ���ڿ��� ���� ���ڿ��� ���Ѵ�.
bool MiniGame::IsCorrect(char input, char text, char* Answer) {//input�� ������� �Է�, Answer�� �ش� ����
	int i = 0;
	if (text == input) {
		*Answer = input;
		return true;
	}
	else {
		return false;
	}
}

void MiniGame::draw_man() {
	int life;

	if (_life >= 6) {
		life = 6;
	}
	else {
		life = _life;
	}
	switch (life) {
	case 6://��ġ ������ �����.
		mConsole->CursorPosition(45, 20);
		cout << "\"�������� �� ������...B+ �̶� ������..\" ";
		mConsole->CursorPosition(45, 8);
		cout << "   _________________ ";
		mConsole->CursorPosition(45, 9);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 10);
		cout << "   |               | ";
		mConsole->CursorPosition(45,11);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 12);
		cout << "                   | ";
		mConsole->CursorPosition(45, 13);
		cout << "                   | ";
		mConsole->CursorPosition(45, 14);
		cout << "                   | ";
		mConsole->CursorPosition(45, 15);
		cout << "                   | ";
		mConsole->CursorPosition(45, 16);
		cout << "                   | ";
		mConsole->CursorPosition(45, 17);
		cout << "                   | ";
		break;
	case 5:
		mConsole->CursorPosition(45, 20);
		cout << " �������� �� ������...B0 �̶� ������...... ";
		mConsole->CursorPosition(45, 8);
		cout << "   _________________ ";
		mConsole->CursorPosition(45, 9);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 10);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 11);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 12);
		cout << "(^ 3 ^)            | ";
		mConsole->CursorPosition(45, 13);
		cout << "                   | ";
		mConsole->CursorPosition(45, 14);
		cout << "                   | ";
		mConsole->CursorPosition(45, 15);
		cout << "                   | ";
		break;
	case 4:
		mConsole->CursorPosition(45, 20);
		cout << " �������� �� ������.........C+ �̶� ������........";
		mConsole->CursorPosition(45, 8);
		cout << "   _________________ ";
		mConsole->CursorPosition(45, 9);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 10);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 11);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 12);
		cout << "(T ^ T)            | ";
		mConsole->CursorPosition(45, 13);
		cout << "  ||               | ";
		mConsole->CursorPosition(45, 14);
		cout << "                   | ";
		mConsole->CursorPosition(45, 15);
		cout << "                   | ";
		break;
	case 3:
		mConsole->CursorPosition(45, 20);
		cout << " �������� �� ������.......��.....C0 �̶� ������...... ";
		mConsole->CursorPosition(45, 8);
		cout << "   _________________ ";
		mConsole->CursorPosition(45, 9);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 10);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 11);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 12);
		cout << "(T _ T)            | ";
		mConsole->CursorPosition(45, 13);
		cout << "--||               | ";
		mConsole->CursorPosition(45, 14);
		cout << "                   | ";
		mConsole->CursorPosition(45, 15);
		cout << "                   | ";
		break;
	case 2:
		mConsole->CursorPosition(45, 20);
		cout << " �������� �� ������.....�Ͼ�.....D+..�ε�....��������?.... ";
		mConsole->CursorPosition(45, 8);
		cout << "   _________________ ";
		mConsole->CursorPosition(45, 9);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 10);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 11);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 12);
		cout << "(T o T)            | ";
		mConsole->CursorPosition(45, 13);
		cout << "--||--             | ";
		mConsole->CursorPosition(45, 14);
		cout << "                   | ";
		mConsole->CursorPosition(45, 15);
		cout << "                   | ";
		break;
	case 1:
		mConsole->CursorPosition(45, 20);
		cout << " �������� �� ������..............��...... ";
		mConsole->CursorPosition(45, 8);
		cout << "   _________________ ";
		mConsole->CursorPosition(45, 9);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 10);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 11);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 12);
		cout << "( T 0 T)           | ";
		mConsole->CursorPosition(45, 13);
		cout << "--||--             | ";
		mConsole->CursorPosition(45, 14);
		cout << " /                 | ";
		mConsole->CursorPosition(45, 15);
		cout << "                   | ";
		break;
	case 0:
		mConsole->CursorPosition(45, 20);
		cout << " �׷�..�� ������ ������ ���� �ʾ�......��2 ";
		mConsole->CursorPosition(45, 8);
		cout << "   _________________ ";
		mConsole->CursorPosition(45, 9);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 10);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 11);
		cout << "   |               | ";
		mConsole->CursorPosition(45, 12);
		cout << "( ^ 3^ )           | ";
		mConsole->CursorPosition(45, 13);
		cout << "--||--             | ";
		mConsole->CursorPosition(45, 14);
		cout << " / |               | ";
		mConsole->CursorPosition(45, 15);
		cout << "                   | ";
		break;
	}
}
MiniGame::MiniGame() {
	_life = 7;
	_score = 0;
	mRandom = Random::Instance();
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();
}
int MiniGame::GetLife() {
	return _life;
}
int MiniGame::GetScore() {
	return  _score;
}
void MiniGame::SetLife(int L) {
	_life = L;
}
void MiniGame::SetLife() {//_SetLife()�� �ѹ� �����ϸ� _life�� �پ���.
	_life--;
}
void MiniGame::SetScore(int S) {
	_score = S;
}


MiniGame* MiniGame::sInstance = nullptr;

MiniGame* MiniGame::Instance()
{
	if (sInstance == nullptr)
		sInstance = new MiniGame;

	return sInstance;
}

void MiniGame::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
