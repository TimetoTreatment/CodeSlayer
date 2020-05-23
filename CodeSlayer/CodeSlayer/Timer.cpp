#include <iostream>
#include "Timer.h"
using namespace std;



void Timer::TypingStart() {
	clock_t s = clock();

	start = (double)s / CLOCKS_PER_SEC;

}

double Timer::TypingEnd() {

	clock_t e = clock();

	double Endsec = (double)e / CLOCKS_PER_SEC;

	duration = Endsec - start;
	
	return duration;
}