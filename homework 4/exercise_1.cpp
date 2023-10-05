/*
File: exercise_1.cpp
Description: Write an openMP program to initialize an array array[] of size 64 to all
1s in parallel using 16 threads, using one parallel construct and/or parallel for.
*/

#include <iostream>
#include <omp.h>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    const int size = 64;

    int array[size];

    ofstream out;

    out.open("Exercise_1_output.txt");

    if (!out)
    {
        return -1;
    }

    #pragma omp parallel for num_threads(16)
    for (int i = 0; i < size; i++) 
    {
        array[i] = 1;
    }

    for (int i = 0; i < size; i++)
        out << array[i] << " ";

    out << endl;

    out.close();

    return 0;
}
