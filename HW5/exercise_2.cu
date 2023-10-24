/*
 Change the size of array[] to 1024 and do what Problem 1 asks
*/



#include <iostream>

#include <cuda.h>

using namespace std;



__global__ void Init_Array()
{

        const int size = 1024;

        int  array[size];

        for(int i = 0; i < size; i++)
        {
                array[i] = 2;
        }

        for(int i = 0; i < size; i++)
        {
                printf("%d ", array[i]);

                if(i % 50 == 0)
                        printf("\n");
        }

        printf("\n");
}




int main()
{

        Init_Array<<<1, 1>>>();

        cudaDeviceSynchronize();

        return 0;

}