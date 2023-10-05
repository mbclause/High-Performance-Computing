/*
File: exercise_3.cpp
Description: In addition to what Exercise 1 and Exercise 2 ask, create another
parallel construct that calculates the number of values divisible by 3 in array[] as follows: it
distributes the iterations to each thread using cyclic distribution, each thread computes the
number of even values from its iterations and master thread collects and adds the number of
even values. Master thread then displays the result.
*/

#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char** argv)
{
    const int size = 64;

    int array[size];

    int tid = 0;

    int local_count = 0;

    int total = 0;

    omp_set_num_threads(16);

    #pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        array[i] = 1;
    }

    #pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        array[i] += i * 2;
    }

    #pragma omp parallel private(tid, local_count) shared(total)
    {
        tid = omp_get_thread_num();

        local_count = 0;

        //the array is distributde statically between threads
        #pragma omp for schedule(static,1)
        for (int i = 0; i < size; i++)
        {
            if (array[i] % 3 == 0)
                local_count++;
        }

        #pragma omp critical
        total += local_count;
    }

    cout << "values divisible by 3: " << total << endl;

    return 0;
}