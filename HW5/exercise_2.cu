/*
Change the size of array[] to 1024 and do what Problem 1 asks.
*/



#include <iostream>

#include <cuda.h>

using namespace std;



// function to initialize the array using the GPU
__global__ void Init_Array(int *array, const int size)
{
        int i = threadIdx.x;

        if(i < size)
                array[i] = 2;
}





int main()
{
	// the size of the array and thus the number of GPU threads
        const int size = 1024;

        int  *deviceArray;

        int  cpuArray[size];

	// allocate memory for the GPU array
        cudaMalloc((void **)&deviceArray, size * sizeof(int));

        dim3   blockSize(size);

        Init_Array<<<1, blockSize>>>(deviceArray, size);

	// copy the array from the GPU to the CPU
        cudaMemcpy(cpuArray, deviceArray, size * sizeof(int), cudaMemcpyDeviceToHost);

	// display the array
        for(int i = 0; i < size; i++)
                cout << cpuArray[i] << " ";

        cout << endl;

        cudaFree(deviceArray);

        return 0;

}