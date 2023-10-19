/*
Write an openMP program to initialize an array[] of size 16 to all 101s in parallel using 8 threads, using one parallel
construct and/or parallel for using block distribution
*/


#include <iostream>
#include <omp.h>

using namespace std;

int main()
{

    const int N = 16;

    int a[N];

    omp_set_num_threads(8);

    #pragma omp parallel
    {
        int t_id = omp_get_thread_num();

        int block_size = N / omp_get_num_threads();

        for (int i = t_id * block_size; i < (t_id + 1) * block_size; i++) 
        {
            a[i] = 101;
        }

    }

    for (int i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }

    cout << endl;

    return 0;
}