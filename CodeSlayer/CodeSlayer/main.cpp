#define TEST 0
// 1로 변경하면 테스트모드가 됩니다.


/* CodeSlayer */
#if !TEST
#include "ProgramManager.h"
int main(void)
{
	ProgramManager::Instance()->MainLoop();
	ProgramManager::Release();

	return 0;
}
#endif


/* Test Site */
#if TEST

#include <iostream>
#include <windows.h>
#include "Timer.h"
#include "TypingManager.h"
#include "Text.h"
#include "Config.h"
#include "MiniGame.h"

int main(void)
{
	/* Timer 테스트 */

	//Timer timer;
	//double elapsedTime;

	//timer.Reset();
	//Sleep(123);
	//elapsedTime = timer.GetElapsedTime();
	//cout << " * Timer : " << elapsedTime << "\n\n";

	///* TypingManager, Text 테스트 */

	//TypingManager* mTypingManager = TypingManager::Instance();
	//Text mShort = mTypingManager->GetRandomText("word");

	//cout << " * Random Word  : " << mShort.GetText() << "\n\n";
	//cout << " * Random Short : " << mTypingManager->GetRandomText("short").GetText() << "\n\n";
	//cout << " * Random Long  : \n\n" << mTypingManager->GetRandomText("long").GetText() << "\n\n";


	///* MiniGame 테스트 */

	//MiniGame miniGame;

	//miniGame.Main();


	/* TypingManager 심층 테스트 */

	TypingManager* mTypingManager = TypingManager::Instance();
	Text mShort = mTypingManager->GetRandomText("word");

}

#endif