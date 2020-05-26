#define DEBUG 0
// 1�� �����ϸ� �׽�Ʈ��尡 �˴ϴ�.

#if !DEBUG
#include "ProgramManager.h"
int main(void)
{
	ProgramManager::Instance()->MainLoop();
	ProgramManager::Release();

	return 0;
}
#endif


#if DEBUG

/* Test Site */
#include <iostream>
#include <windows.h>
#include "Timer.h"
#include "TypingManager.h"
#include "Text.h"
#include "Config.h"
#include "MiniGame.h"

int main(void)
{
	///* Timer �׽�Ʈ */

	//Timer timer;
	//double elapsedTime;

	//timer.Reset();
	//Sleep(123);
	//elapsedTime = timer.GetElapsedTime();
	//cout << " * Timer : " << elapsedTime << "\n\n";

	///* TypingManager, Text �׽�Ʈ */

	//TypingManager* mTypingManager = TypingManager::Instance();
	//Text mShort = mTypingManager->GetRandomText("word");

	//cout << " * Random Word  : " << mShort.GetText() << "\n\n";
	//cout << " * Random Short : " << mTypingManager->GetRandomText("short").GetText() << "\n\n";
	//cout << " * Random Long  : \n\n" << mTypingManager->GetRandomText("long").GetText() << "\n\n";

	MiniGame miniGame;

	miniGame.Main();



}

#endif