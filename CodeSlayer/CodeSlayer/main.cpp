#include "ProgramManager.h"


int main(void)
{
	ProgramManager::Instance()->MainLoop();
	ProgramManager::Release();

	return 0;
}