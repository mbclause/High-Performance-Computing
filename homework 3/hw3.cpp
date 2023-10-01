/*
File: HW3.cpp
Description: Contains the function definition.
*/

#include "HW3.h"
#include <iostream>

using namespace std;


/*
Function: FormatTime
Description: Takes the total number of minutes and converts that time to hours and minutes. Both values returned by reference.
*/
void  FormatTime(int& hrs, int& min)
{
	hrs = min / 60;

	min %= 60;
}