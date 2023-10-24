/*
 Create another kernel that adds i to array[i] and do what Problem 1
and Problem 2 ask.
*/



#include <iostream>

#include <cuda.h>

using namespace std;




__device__  void  Add_Array(int array[], int size)
{
        for(int i = 0; i < size; i++)
        {
                array[i] += i;
        }

        for(int i = 0; i < size; i++)
        {
                printf("%d ", array[i]);

                if(i % 50 == 0)
                        printf("\n");
        }

        printf("\n");
}





__global__ void Init_Array()
{

        const int size = 1024;

        int  array[size];

        for(int i = 0; i < size; i++)
        {
                array[i] = 2;
        }

        Add_Array(array, size);
}



int main()
{

        Init_Array<<<1, 1>>>();

        cudaDeviceSynchronize();

        return 0;

}