//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 미니 게임
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- C++ 코드 빈칸 맞추기 게임

	2. 기능
		- 시작 화면, 게임 화면, 결과 화면
		- 빈칸을 틀릴 때마다 사람 그림이 완성
		- 사람 그림이 완성되면 사망
*/

#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Random.h"
#include "Console.h"
#include "Config.h"
#include "Keyboard.h"
#include "Text.h"

using namespace std;


class MiniGame
{
private:

	Console* mConsole;
	Keyboard* mKeyboard;
	Random* mRandom;

	const int mXPosCin = 29;
	const int mYPosCin = 41;
	const int mWidthCinBox = 11;
	const int mHeightCinBox = 1;

	const int mXPosCout = 91;
	const int mYPosCout = 41;
	const int mWidthCoutBox = 11;
	const int mHeightCoutBox = 1;

	const int mXPosCorrect = 63;
	const int mYPosCorrect = 41;

	const int mXPosPresetCodeStart = 11;
	const int mYPosPresetCodeStart = 16;
	const int mXPosUserCodeStart = 72;
	const int mYPosUserCodeStart = 17;

	const int mXPosUserScript = 78;
	const int mYPosUserScript = 20;

	const int mWidthCodeBox = 51;
	const int mHeightCodeBox = 23;

	const int mXPosGallows = 85;
	const int mYPosGallows = 25;

	const int mXPosTitleStart = 54;
	const int mYPosTitleStart = 10;

	const int mXPosPrompt = 53;
	const int mYPosPrompt = 23;
	const int mXPosTrafficLight = 58;
	const int mYPosTrafficLight = 19;

	const int mXPosEnding = 73;
	const int mYPosEnding = 32;

	const int mStartLife = 8;
	int mLife = 0;

	bool mQuit = false;

	unordered_map<int, string> mLifeToGrade = {
	{8, "A+"},
	{7, "A0"},
	{6, "B+"},
	{5, "B0"},
	{4, "C+"},
	{3, "C0"},
	{2, "D+"},
	{1, "D0"},
	{0, "F"},
	};

	vector<Text> mPresetCodes;
	vector<Text> mPresetAnswers;

	void LoadTextFiles();		// 프리셋 텍스트 파일 로드

	vector<int> mRandomTable;	// 난수 테이블
	int mRandomTableIndex;		// 테이블 선택 인덱스

	void SetRandomTable();		// 난수 테이블 생성
	int GetRandomTableNum();	// 난수 테이블 값 반환

	MiniGame();

	enum class Ending
	{
		yes,
		no
	};

	/* 행맨 그리기 */
	void DrawHangman(Ending isEnding);

	/* 시작 화면 */
	void RenderIntro();

	/* 게임 */
	void RenderGame();

	/* 종료 화면 */
	void RenderResult();

public:
	
	/* 메인 */
	void Main();


private:
	static MiniGame* sInstance;

public:
	static MiniGame* Instance();
	static void Release();
};