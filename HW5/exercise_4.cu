/*
 Change the size of array[] to 8000 and do what Problem 1 and
Problem 2 ask. Check if you are still able to do what Problem 1 and Problem 2 ask
*/



#include <iostream>

#include <cuda.h>

using namespace std;








__global__ void Init_Array()
{

        const int size = 8000;

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