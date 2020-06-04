#include"MiniGame.h"
//#include"console.h"
//#include "Random.h"
// -> 헤더 파일로 옮겼습니다.

using namespace std;

void MiniGame::Main() {//게임의 전체적인 흐름을 관리한다.
	char input;

	mConsole->Color("white");
	string Answer;
	int cnt = 0;

	int count;
	int len;
	string path;
	string line;
	string Game, GameAns;//Game은 입력받는 문장이다. GameAns는 정답 문장이다.
	fstream file;

	int rand;
	rand = mRandom->Integer(0, 2);//숫자는 변경한다. 미완성이기에 적은 범위로 만들었다.

	//--------------------------문서를 입력받는다---------------------//
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
	//--------------------------정답를 입력받는다---------------------//
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

	//------------------------파일 입력을 종료한다.---------------------//


	int Answer_len = GameAns.length();
	int i = 0;
	for (i = 0; i < Answer_len; i++) {
		Answer += '_';
	}
	SetLife(Answer_len + 3);//문제의 길이보다 기회를 3번 더 준다.

	while (1) {
		mConsole->CursorPosition(5, 5);
		cout << Game << endl;
		mConsole->CursorPosition(95, 5);
		cout << "Life : " << GetLife() << endl;;//목숨 출력
		mConsole->CursorPosition(95, 7);
		cout << "Score : " << GetScore() << endl;;//점수 출력
		mConsole->CursorPosition(85, 23);
		cout << Answer;
		mConsole->CursorPosition(45, 23);
		cout << "순서대로 빈칸에 문자를 넣어주세요 ==>>";
		mConsole->CursorPosition(45, 26);
		cout << "입력 : ";
		cin >> input;//해당칸의 문자를 넣는다.
		//--------------------------------수정본------------------------------------------------//
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
			SetLife();//목숨이 줄어든다.
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
		cout << "너의 정답 ==>>";
		mConsole->CursorPosition(60, 23);
		cout << Answer;
		mConsole->CursorPosition(45, 25);
		cout << "생존할 수 있었습니다.";
	}
	if (GetLife() == 0) {
		mConsole->Clear();
		draw_man();
		mConsole->CursorPosition(45, 25);
		cout << " 전과하였습니다. ";
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
//사용자가 입력한 문자열과 정답 문자열을 비교한다.
bool MiniGame::IsCorrect(char input, char text, char* Answer) {//input은 사용자의 입력, Answer은 해당 문자
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
	case 6://위치 설정이 힘들다.
		mConsole->CursorPosition(45, 20);
		cout << "\"아직까지 내 학점은...B+ 이라서 괜찮아..\" ";
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
		cout << " 아직까지 내 학점은...B0 이라서 괜찮아...... ";
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
		cout << " 아직까지 내 학점은.........C+ 이라서 괜찮아........";
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
		cout << " 아직까지 내 학점은.......하.....C0 이라서 괜찮아...... ";
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
		cout << " 아직까지 내 학점은.....하아.....D+..인데....괜찮을까?.... ";
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
		cout << " 아직까지 내 학점은..............하...... ";
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
		cout << " 그래..이 전공은 나한테 맞지 않아......ㅃ2 ";
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
void MiniGame::SetLife() {//_SetLife()를 한번 실행하면 _life가 줄어든다.
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
