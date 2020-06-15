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
	int mRecentResultNum = 0;

	const int mTestCase = 3;

	void RenderIntro();
	void RenderPractice();
	void RenderResult();

	void ReadResultFile();
	void WriteResultFile();

	size_t Whitespace(const string& currentLine) const;
	void OrganizeCode(string& currentLine);
	bool IsOperator(char ch) const;

public:

	void Main();


private:
	static LongPractice* sInstance;

public:
	static LongPractice* Instance();
	static void Release();
};
