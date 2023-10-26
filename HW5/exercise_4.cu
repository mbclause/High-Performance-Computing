/*
Change the size of array[] to 8000 and do what Problem 1 and Problem 2 ask. Check if you are still able to do what Problem 1 and Problem 2 asks.
*/



#include <iostream>

#include <cuda.h>

using namespace std;



// initialze the array using the gpu
__global__ void Init_Array(int *array, const int size)
{
        int i = threadIdx.x;

        if(i < size)
                array[i] = 2;
}



int main()
{
	// size of array and number of threads is 8000
        const int size = 8000;

        int  *deviceArray;

        int  cpuArray[size];

	// allocate array memory on GPU
        cudaMalloc((void **)&deviceArray, size * sizeof(int));

        dim3   blockSize(size);

        Init_Array<<<1, blockSize>>>(deviceArray, size);

	// copy gpu array to cpu array
        cudaMemcpy(cpuArray, deviceArray, size * sizeof(int), cudaMemcpyDeviceToHost);

	// display array, because 8000 is too many threads, array values will not be initialize to 2
        for(int i = 0; i < size; i++)
                cout << cpuArray[i] << " ";

        cout << endl;

        cudaFree(deviceArray);

        return 0;

}