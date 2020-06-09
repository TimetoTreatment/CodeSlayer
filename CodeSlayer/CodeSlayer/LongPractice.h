#pragma once
#include "TypingManager.h"


class LongPractice : protected TypingManager
{
private:

	LongPractice();
	~LongPractice();

	vector<Text> mPresetCodes;
	queue<int> mRecentAccuracy;
	queue<int> mRecentSpeed;
	int mRecentResultNum;

	const int mTestCase = 5;

	void RenderIntro();
	void RenderPractice();
	void RenderResult();

	void ReadResultFile();
	void WriteResultFile();
	size_t Whitespace(const string& currentLine);
	void OrganizeCode(string& currentLine);
	bool IsOperator(char ch);

public:

	void Main();


private:
	static LongPractice* sInstance;

public:
	static LongPractice* Instance();
	static void Release();
};
