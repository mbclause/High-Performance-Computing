/*
Write a CUDA program to initialize an array array[] of size 64 to all 2s
in parallel.
*/



#include <iostream>

#include <cuda.h>

using namespace std;



__global__ void Init_Array()
{

        const int size = 64;

        int  array[size];

        for(int i = 0; i < size; i++)
        {
                array[i] = 2;
        }

        for(int i = 0; i < size; i++)
        {
                printf("%d ", array[i]);
        }

        printf("\n");
}




int main()
{

        Init_Array<<<1, 5>>>();

        cudaDeviceSynchronize();

        return 0;

}