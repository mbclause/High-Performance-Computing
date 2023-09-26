#include "hw3.h"
#include <iostream>

using namespace std;

void  FormatTime(int& hrs, int& min)
{
	hrs = min / 60;

	min %= 60;
}