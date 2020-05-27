#include"MiniGame.h"
//#include"console.h"
//#include "Random.h"
// -> 헤더 파일로 옮겼습니다.


void MiniGame::Main() {//게임의 전체적인 흐름을 관리한다.
    char input;
    Console* mConsole;
    Random* mRandom;
    MiniGame mMiniGame;
    mRandom = Random::Instance();
    mConsole = Console::Instance();
    mConsole->Color("white");
    string Answer;
    int cnt = 0;
    mMiniGame.SetConsoleSize();//콘솔의 크기를 조절합니다.

    string text;//입력받는 문장
    //--------------------------------------------------------------//
    text = "GoHome";//예시 문장이다.import를 통해 text를 변경한다.-//
    //--------------------------------------------------------------//
    int num = 0;
    //----------------------------------------------------------//
    num = mRandom->Integer(1, 5);//수정 가능--------------------//
    //----------------text들 중에서 고른다.---------------------//
    //임의의 text를 받는다. 일단 공백..
    int Answer_len = text.length();
    int i = 0;
    for (i = 0; i < Answer_len; i++) {
        Answer += '_';
    }
    mMiniGame.SetLife(Answer_len + 3);//문제의 길이보다 기회를 3번 더 준다.

    while (1) {
        mConsole->CursorPosition(5, 5);
        cout << "Life : " << mMiniGame.GetLife() << endl;;//목숨 출력
        mConsole->CursorPosition(5, 7);
        cout << "Score : " << mMiniGame.GetScore() << endl;;//점수 출력
        mConsole->CursorPosition(5, 18);
        cout << Answer;
        mConsole->CursorPosition(5, 20);
        cout << "순서대로 빈칸에 문자를 넣어주세요";
        mConsole->CursorPosition(5, 22);
        cout << "입력 : ";
        cin >> input;//해당칸의 문자를 넣는다.
        cout << endl;
        if (IsCorrect(input, text[cnt], &Answer[cnt]) == false) {
            mMiniGame.SetLife();//목숨이 줄어든다.
            mConsole->CursorPosition(10, 13);
            cout << "Bad" << endl;
        }
        else {//맞힌 개수
            Answer[cnt] = input;
            cnt++;
            mConsole->CursorPosition(10, 13);
            cout << "Good"<<endl;
        }
        mMiniGame.draw_man();

        if (cnt == text.length()) {
            break;
        }
        if (mMiniGame.GetLife() == 0) {
            break;
        }
    }
    if (cnt == text.length()) {
        mConsole->Clear();
        mConsole->CursorPosition(65, 33);
        cout << "생존할 수 있었습니다." << endl;
    }
    if (mMiniGame.GetLife() == 0) {
        mConsole->Clear();
        mMiniGame.draw_man();
        mConsole->CursorPosition(65, 33);
        cout << " 전과하였습니다. " << endl;
    }

    for(;;)
    { }

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
void MiniGame::SetConsoleSize() {
    system("mode con:cols=130 lines=45");

}
void MiniGame::draw_man() {
    int life;
    Console* mConsole;
    mConsole = Console::Instance();
    if (_life >= 6) {
        life = 6;
    }
    else {
        life = _life;
    }
    switch (life) {
    case 6://위치 설정이 힘들다.
        mConsole->CursorPosition(65, 30);
        cout << " 아직까지 내 학점은...B+ 이라서 괜찮아.. ";
        mConsole->CursorPosition(65, 17);
        cout << "   _________________ ";
        mConsole->CursorPosition(65,18);
        cout << "   |               | ";
        mConsole->CursorPosition(65,19);
        cout << "   |               | ";
        mConsole->CursorPosition(65,20);
        cout << "   |               | ";
        mConsole->CursorPosition(65,21);
        cout << "                   | ";
        mConsole->CursorPosition(65,22);
        cout << "                   | ";
        mConsole->CursorPosition(65, 23);
        cout << "                   | ";
        mConsole->CursorPosition(65, 24);
        cout << "                   | ";
        mConsole->CursorPosition(65, 25);
        cout << "                   | ";
        mConsole->CursorPosition(65, 26);
        cout << "                   | ";
        break;
    case 5:
        mConsole->CursorPosition(65, 30);
        cout << " 아직까지 내 학점은...B0 이라서 괜찮아...... ";
        mConsole->CursorPosition(65, 17);
        cout << "   _________________ ";
        mConsole->CursorPosition(65, 18);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 19);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 20);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 21);
        cout << "(^ 3 ^)            | ";
        mConsole->CursorPosition(65, 22);
        cout << "                   | ";
        mConsole->CursorPosition(65, 23);
        cout << "                   | ";
        mConsole->CursorPosition(65, 24);
        cout << "                   | ";
        break;
    case 4:
        mConsole->CursorPosition(65, 30);
        cout << " 아직까지 내 학점은.........C+ 이라서 괜찮아........";
        mConsole->CursorPosition(65, 17);
        cout << "   _________________ ";
        mConsole->CursorPosition(65, 18);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 19);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 20);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 21);
        cout << "(T ^ T)            | ";
        mConsole->CursorPosition(65, 22);
        cout << "  ||               | ";
        mConsole->CursorPosition(65, 23);
        cout << "                   | ";
        mConsole->CursorPosition(65, 24);
        cout << "                   | ";
        break;
    case 3:
        mConsole->CursorPosition(65, 30);
        cout << " 아직까지 내 학점은.......하.....C0 이라서 괜찮아...... ";
        mConsole->CursorPosition(65, 17);
        cout << "   _________________ ";
        mConsole->CursorPosition(65, 18);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 19);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 20);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 21);
        cout << "(T _ T)            | ";
        mConsole->CursorPosition(65, 22);
        cout << "--||               | ";
        mConsole->CursorPosition(65, 23);
        cout << "                   | ";
        mConsole->CursorPosition(65, 24);
        cout << "                   | ";
        break;
    case 2:
        mConsole->CursorPosition(65, 30);
        cout << " 아직까지 내 학점은.....하아.....D+..인데....괜찮을까?.... ";
        mConsole->CursorPosition(65, 17);
        cout << "   _________________ ";
        mConsole->CursorPosition(65, 18);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 19);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 20);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 21);
        cout << "(T o T)            | ";
        mConsole->CursorPosition(65, 22);
        cout << "--||--             | ";
        mConsole->CursorPosition(65, 23);
        cout << "                   | ";
        mConsole->CursorPosition(65, 24);
        cout << "                   | ";
        break;
    case 1:
        mConsole->CursorPosition(65, 30);
        cout << " 아직까지 내 학점은..............하...... ";
        mConsole->CursorPosition(65, 17);
        cout << "   _________________ ";
        mConsole->CursorPosition(65, 18);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 19);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 20);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 21);
        cout << "( T 0 T)           | ";
        mConsole->CursorPosition(65, 22);
        cout << "--||--             | ";
        mConsole->CursorPosition(65, 23);
        cout << " /                 | ";
        mConsole->CursorPosition(65, 24);
        cout << "                   | ";
        break;
    case 0:
        mConsole->CursorPosition(65, 30);
        cout << " 그래..이 전공은 나한테 맞지 않아......ㅃ2 ";
        mConsole->CursorPosition(65, 17);
        cout << "   _________________ ";
        mConsole->CursorPosition(65, 18);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 19);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 20);
        cout << "   |               | ";
        mConsole->CursorPosition(65, 21);
        cout << "( ^ 3^ )           | ";
        mConsole->CursorPosition(65, 22);
        cout << "--||--             | ";
        mConsole->CursorPosition(65, 23);
        cout << " / |               | ";
        mConsole->CursorPosition(65, 24);
        cout << "                   | ";
        break;
    }
}
MiniGame::MiniGame() {
    _life = 7;
    _score = 0;
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